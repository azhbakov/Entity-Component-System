#include <memory>
#include <src/GUI/include/ScrollPanel.hpp>
#include <src/GUI/include/ScrollPanelElement.hpp>
#include <src/GUI/include/BoxLayout.hpp>
#include <src/GUI/include/Image.hpp>

#include "Loader.hpp"
#include "Camera.hpp"
#include "SpriteRenderer.hpp"
#include "CircleRenderer.hpp"
#include "MovementScript.hpp"
#include "BoxCollider.hpp"
#include "LabelElement.hpp"
#include "Tags.hpp"
#include "config.hpp"

#ifdef ENABLE_LOG
#include "Logger.hpp"
#endif

using namespace un;
using namespace std;

int Loader::RenderTest (Game& game, sf::RenderWindow& window, ResourceManager& _resourceManager) {
	Logger& logger = Logger::Instance();

	logger.Log ({"DIRECT"}, "Creating camera object.");
	weak_ptr<GameObject> cameraObject = game.Instantiate ("Camera");
	cameraObject.lock()->SetTag(CAMERA_TAG);
	logger.Log ({"DIRECT"}, "Created camera object.");

	logger.Log ({"DIRECT"}, "Adding camera component.");
	cameraObject.lock()->AddComponent<Camera>(window, 800, 600);
	logger.Log ({"DIRECT"}, "Added camera component.");

	logger.Log ({"DIRECT"}, "Creating sprite object.");
	weak_ptr<GameObject> spriteObject1 = game.Instantiate ("Spriter1");
	logger.Log ({"DIRECT"}, "Created sprite object.");

	logger.Log ({"DIRECT"}, "Creating sprite object.");
	weak_ptr<GameObject> spriteObject2 = game.Instantiate ("Spriter2");
	logger.Log ({"DIRECT"}, "Created sprite object.");

	sf::Texture& tex = _resourceManager.LoadTexture(DATA_PATH"foo.png", "man");

	logger.Log ({"DIRECT"}, "Adding sprite component.");
	spriteObject1.lock()->AddComponent<SpriteRenderer>(1, tex);
	logger.Log ({"DIRECT"}, "Added sprite component.");

	sf::Texture& tex2 = _resourceManager.LoadTexture(DATA_PATH"background.png", "background");

	logger.Log ({"DIRECT"}, "Adding sprite component.");
	spriteObject2.lock()->AddComponent<SpriteRenderer>(0, tex2);
	logger.Log ({"DIRECT"}, "Added sprite component.");

	// Point player GO
	logger.Log ({"DIRECT"}, "Creating sprite object.");
	weak_ptr<GameObject> playerObject = game.Instantiate ("Player");
	logger.Log ({"DIRECT"}, "Created sprite object.");
	// Point player renderer
	logger.Log ({"DIRECT"}, "Adding sprite component.");
	playerObject.lock()->AddComponent<CircleRenderer>(3, 5);
	logger.Log ({"DIRECT"}, "Added sprite component.");
	// Movement
	logger.Log ({"DIRECT"}, "Adding Movement component.");
	playerObject.lock()->AddComponent<MovementScript>(0.01f);
	logger.Log ({"DIRECT"}, "Added Movement component.");

	auto& groundTex = _resourceManager.LoadTexture(DATA_PATH"mud_wall.png", "mud", true);
	weak_ptr<GameObject> groundObject = game.Instantiate ("Ground");
	auto groundSprite = groundObject.lock()->AddComponent<SpriteRenderer>(2, groundTex);
	(*(groundSprite.lock()))->setTextureRect(sf::IntRect(0, 0, 500, 500));

	return 0;
}

int Loader::Box2DTest(SFMLGame& sgame) {
	auto& window = sgame.GetRenderWindow();
	auto& game = sgame.GetGame();
	auto& resourceManager = sgame.GetResourceManager ();
	auto& physicsSubsystem = sgame.GetPhysicsSubsystem ();

	int ppu = Game::Instance().PIXELS_PER_UNIT;

	/* Camera Object */
	auto cameraObject = game.Instantiate ("Camera");
	cameraObject.lock()->SetTag(CAMERA_TAG);
	auto camera = cameraObject.lock()->AddComponent<Camera> (window, 800, 600);
	auto cameraMovement = cameraObject.lock()->AddComponent<MovementScript>(0.1f);

	/* Box Object */
	auto boxObject = game.Instantiate ("Box1", 0, 2);
	float width = 1.0f;
	float height = 1.0f;

	auto boxCollider = boxObject.lock()->AddComponent<BoxCollider> (physicsSubsystem, width, height);

	sf::Texture& boxTex = resourceManager.LoadTexture(DATA_PATH"box.png", "box", true);
	auto boxSprite = boxObject.lock()->AddComponent<SpriteRenderer> (1, boxTex);
	boxSprite.lock()->SetSize(width, height);

	/* Box Object 2 */
	auto boxObject2 = game.Instantiate ("Box2", 0.5, 0);

	auto boxCollider2 = boxObject2.lock()->AddComponent<BoxCollider> (physicsSubsystem, width, height);
	auto boxSprite2 = boxObject2.lock()->AddComponent<SpriteRenderer> (1, boxTex);
	boxSprite2.lock()->SetSize(width, height);


	/* Ground Object */
	float groundWidth = 50.0f;
	float groundHeight = 1.0f;
	auto groundObject = game.Instantiate ("Ground", 0, -1.0f);

	auto groundCollider = groundObject.lock()->AddComponent<BoxCollider> (physicsSubsystem, groundWidth, groundHeight, false);

	sf::Texture& mudTex = resourceManager.LoadTexture(DATA_PATH"mud_wall.png", "mud", true);
	auto groundSprite = groundObject.lock()->AddComponent<SpriteRenderer> (1, mudTex);
	groundSprite.lock()->SetTextureRect (0,0,groundWidth*ppu, groundHeight*ppu);
	groundSprite.lock()->SetSize(groundWidth, groundHeight);

	/* GUI */
	auto& font = resourceManager.LoadFont (DATA_PATH"DejaVuSansMono.ttf", "DejaVu");

	auto* scrollPanelElement = new ScrollPanelElement (window, 0.3f, 0.3f, 200, 200);

	auto* panel = new BoxLayout ();

	sf::Sprite sprite;
	sprite.setTexture(mudTex);
	panel->AddComponent(new Image(sprite));

	sf::Sprite sprite2;
	sprite2.setTexture(boxTex);
	panel->AddComponent(new Image(sprite2));

	auto* azazLabel = new Label ("AZAZAZZAZAZAZAZAZAZAZAZAZ", font, 50);
	auto *azazLabelScroll = new ScrollPanel (panel->GetWidth(), azazLabel->GetHeight()+20);
	azazLabelScroll->SetContent(azazLabel);
	panel->AddComponent(azazLabelScroll);

	scrollPanelElement->GetScrollPanel().SetContent(panel);
	game.RegisterGUIElement(scrollPanelElement);

	return 0;
}