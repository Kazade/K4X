
#include <k4x/k4x.h>

void on_one_player(k4x::Engine& engine) {
    engine.set_player_mode(k4x::SINGLE_PLAYER);
    engine.chapter_manager().switch_to_chapter("save_selection");
}

void on_two_player(k4x::Engine& engine) {
    engine.set_player_mode(k4x::TWO_PLAYER);
    engine.chapter_manager().switch_to_chapter("save_selection");
}

int main(int argc, char* argv[]) {
    
    k4x::Engine engine(argc, argv);

    engine.window().set_title("Sonic 1 4X");
    engine.title().set_background_image("s14x/resources/title/background.png"); //Give the title screen a background
    engine.chapter_manager().switch_to_chapter("title");

/*
    //Configure the title screen
    engine.title().add_demo("s14x/demos/demo_1.ogv"); //Add a list of demo moves that cycle after a timeout
    engine.title().add_demo("s14x/demos/demo_2.ogv");
    engine.title().set_time_to_demo(30); //Set the time the title screen shows before displaying a demo
    engine.title().set_fade_time(1); //Set the fade time when time_to_demo runs out
    engine.title().set_background_music("s14x/music/intro.ogg"); //Set the background music
    engine.title().set_background_image("s14x/backgrounds/title.png");
    engine.title().add_animated_sprite("s14x/title/main_sprite.png", k4x::POSITION_CENTERED);

    //On menu selection, go to the save_selection screen
    engine.title().menu().add_entry("1 Player", &on_one_player());
    engine.title().menu().add_entry("2 Player", &on_two_player());
    engine.title().menu().add_entry("Exit", sigc::bind(&Engine::shutdown, &engine));

    //Register a single level, we need to also register any actors and gimmicks that the level file refers to.
    k4x::LevelID green_hill = engine.level_manager().add_level("s1x/levels/green_hill_act_one.k4x", "s14x/levels/green_hill_act_two.k4x");
    engine.level_manager().level(green_hill).register_actor_type("crabmeat", s14x::actors::CrabMeatFactory::create());
    engine.level_manager().level(green_hill).register_actor_type("pendulum_boss", s14x::actors::PendulumBossFactory::create());
    engine.level_manager().level(green_hill).register_gimmick("wooden_bridge", s14x::gimmicks::WoodenBridgeFactory::create());

    //Show the following entries in the pause menu, "Unpause" always exists
    engine.level_manager().pause_menu().add_entry("Retry", sigc::bind(&ChapterManger::restart_current, engine.chapter_manager()));
    engine.level_manager().pause_menu().add_entry("Quit", sigc::bind(&Engine::select_chapter, &engine, "title"));

    //Add extra game logic processing during levels (e.g. keeping score, updating life counts etc.)
    engine.level_manager().set_level_logic(s14x::LevelLogic::create());

    //Each player can have a profile with extra attributes (e.g. score, rings, lives etc.), this specifies the factory for that.
    engine.set_player_profile_factory(s14x::PlayerProfileFactory::create());
*/
    return engine.run();
}
