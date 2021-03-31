#include "ingamestate.h"

InGameState::InGameState(gef::SpriteRenderer* sprite_renderer, gef::Renderer3D* renderer_3d, gef::Font* font, Camera* camera, gef::Platform* platform, std::vector<State*> &states) :
	sprite_renderer_(sprite_renderer),
	renderer_3d_(renderer_3d),
	font_(font),
	camera_(camera),
	world_(NULL),
	player_(NULL),
	platform_(platform),
	states_(states)
	
{
	// initialise primitive builder to make create some 3D geometry easier
	primitive_builder_ = new PrimitiveBuilder(*platform_);

	// create the renderer for draw 3D geometry
	renderer_3d_ = gef::Renderer3D::Create(*platform_);

	player_ = new Player(); // init player

	SetupLights();

	// initialise the physics world
	b2Vec2 gravity(0.0f, -9.81f);
	world_ = new b2World(gravity);

	player_->Init(primitive_builder_, world_);
	InitGround();
}

InGameState::~InGameState()
{
	// destroying the physics world also destroys all the objects within it
	delete world_;
	world_ = NULL;

	delete ground_mesh_;
	ground_mesh_ = NULL;

	delete primitive_builder_;
	primitive_builder_ = NULL;

	delete renderer_3d_;
	renderer_3d_ = NULL;
}

void InGameState::onEnter()
{

}

void InGameState::onExit()
{
	
}

State* InGameState::Update(float frame_time, const gef::SonyController* controller)
{
	UpdateSimulation(frame_time, controller);

	camera_->setTarget(gef::Vector4(player_->getPosition().x, player_->getPosition().y, 0.f, 0.f));
	camera_->Update();

	if (controller->buttons_pressed() & gef_SONY_CTRL_R2) {
		return states_[MENUSTATE];
	}
	return this;
}

void InGameState::Render()
{
	// projection
	renderer_3d_->set_projection_matrix(camera_->getProjectionMatrix());

	// view
	renderer_3d_->set_view_matrix(camera_->getViewMatrix());

	// draw 3d geometry
	renderer_3d_->Begin();

	// draw ground
	renderer_3d_->DrawMesh(ground_);

	// draw player
	renderer_3d_->set_override_material(&primitive_builder_->red_material());
	renderer_3d_->DrawMesh(*player_);
	renderer_3d_->set_override_material(NULL);

	renderer_3d_->End();

	// start drawing sprites, but don't clear the frame buffer
	sprite_renderer_->Begin(false);
	//DrawHUD();
	sprite_renderer_->End();
}

void InGameState::SetupLights()
{
	// grab the data for the default shader used for rendering 3D geometry
	gef::Default3DShaderData& default_shader_data = renderer_3d_->default_shader_data();

	// set the ambient light
	default_shader_data.set_ambient_light_colour(gef::Colour(0.25f, 0.25f, 0.25f, 1.0f));

	// add a point light that is almost white, but with a blue tinge
	// the position of the light is set far away so it acts light a directional light
	gef::PointLight default_point_light;
	default_point_light.set_colour(gef::Colour(0.7f, 0.7f, 1.0f, 1.0f));
	default_point_light.set_position(gef::Vector4(-500.0f, 400.0f, 700.0f));
	default_shader_data.AddPointLight(default_point_light);
}

void InGameState::InitGround()
{
	// ground dimensions
	gef::Vector4 ground_half_dimensions(5.0f, 0.5f, 0.5f);

	// setup the mesh for the ground
	ground_mesh_ = primitive_builder_->CreateBoxMesh(ground_half_dimensions);
	ground_.set_mesh(ground_mesh_);

	// create a physics body
	b2BodyDef body_def;
	body_def.type = b2_staticBody;
	body_def.position = b2Vec2(0.0f, 0.0f);

	ground_body_ = world_->CreateBody(&body_def);

	// create the shape
	b2PolygonShape shape;
	shape.SetAsBox(ground_half_dimensions.x(), ground_half_dimensions.y());

	// create the fixture
	b2FixtureDef fixture_def;
	fixture_def.shape = &shape;

	// create the fixture on the rigid body
	ground_body_->CreateFixture(&fixture_def);

	// update visuals from simulation data
	ground_.UpdateFromSimulation(ground_body_);
}

void InGameState::UpdateSimulation(float frame_time, const gef::SonyController* controller)
{
	// update physics world
	float timeStep = 1.0f / 60.0f;

	int32 velocityIterations = 6;
	int32 positionIterations = 2;

	world_->Step(timeStep, velocityIterations, positionIterations);

	// update object visuals from simulation data
	player_->Update(frame_time, controller);

	// don't have to update the ground visuals as it is static

	// collision detection
	// get the head of the contact list
	b2Contact* contact = world_->GetContactList();
	// get contact count
	int contact_count = world_->GetContactCount();

	for (int contact_num = 0; contact_num < contact_count; ++contact_num)
	{
		if (contact->IsTouching())
		{
			// get the colliding bodies
			b2Body* bodyA = contact->GetFixtureA()->GetBody();
			b2Body* bodyB = contact->GetFixtureB()->GetBody();
	
			// DO COLLISION RESPONSE HERE
			Player* player = NULL;
	
			GameObject* gameObjectA = NULL;
			GameObject* gameObjectB = NULL;
	
			gameObjectA = reinterpret_cast<GameObject*>(bodyA->GetUserData().pointer);
			gameObjectB = reinterpret_cast<GameObject*>(bodyB->GetUserData().pointer);
	
			if (gameObjectA)
			{
				if (gameObjectA->type() == PLAYER)
				{
					player = reinterpret_cast<Player*>(bodyA->GetUserData().pointer);
				}
			}
	
			if (gameObjectB)
			{
				if (gameObjectB->type() == PLAYER)
				{
					player = reinterpret_cast<Player*>(bodyB->GetUserData().pointer);
				}
			}
	
			if (player)
			{
				// take damage / play sound
			}
		}
	
		// Get next contact point
		contact = contact->GetNext();
	}
}