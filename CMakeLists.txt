cmake_minimum_required(VERSION 3.20)

set(APPNAME SpaceInvaders)
project(${APPNAME} VERSION 1.0 LANGUAGES C)

find_package(SDL2 REQUIRED)
find_package(SDL2_image REQUIRED)
find_package(SDL2_mixer REQUIRED)

include_directories(${SDL2_INCLUDE_DIRS} ${SDL2_IMAGE_INCLUDE_DIRS} ${SDL2_MIXER_INCLUDE_DIRS})

include_directories(src/core src/core/GameObjects)

list(APPEND GameSources
	src/classes/Player.h
	src/classes/Player.c
	src/classes/Enemy.h
	src/classes/Enemy.c
	src/classes/Enemies.h
	src/classes/Enemies.c
	src/classes/EnemiesList.h
	src/classes/EnemiesList.c
	src/classes/GroupAttack.h
	src/classes/GroupAttack.c
	src/classes/BurstAttack.h
	src/classes/BurstAttack.c
	src/classes/SideAttack.h
	src/classes/SideAttack.c
	src/classes/Bullet.h
	src/classes/Bullet.c
	src/classes/Bullets.h
	src/classes/Bullets.c
	src/classes/BulletList.h
	src/classes/BulletList.c
	src/classes/Score.h
	src/classes/Score.c
	src/classes/HUD.h
	src/classes/HUD.c

	src/Game.h
	src/Game.c

	src/Global.h
)

list(APPEND CoreSources
	src/core/Engine.h
	src/core/Engine.c

	src/core/TextureManager.h
	src/core/TextureManager.c
	src/core/SoundManager.h
	src/core/SoundManager.c

	src/core/GameObjects/GameObjects.h
	src/core/GameObjects/Structs.h
	src/core/GameObjects/GameObject.h
	src/core/GameObjects/GameObject.c
	src/core/GameObjects/Image.h
	src/core/GameObjects/Image.c
	src/core/GameObjects/PhysicsBody.h
	src/core/GameObjects/PhysicsBody.c
	src/core/GameObjects/Sprite.h
	src/core/GameObjects/Sprite.c
	src/core/GameObjects/Animation.h
	src/core/GameObjects/Animation.c
	src/core/GameObjects/AnimatedSprite.h
	src/core/GameObjects/AnimatedSprite.c
	src/core/GameObjects/Solid.h
	src/core/GameObjects/Solid.c
	src/core/GameObjects/BitmapChar.h
	src/core/GameObjects/BitmapChar.c
	src/core/GameObjects/BitmapFont.h
	src/core/GameObjects/BitmapFont.c
	src/core/GameObjects/BitmapText.h
	src/core/GameObjects/BitmapText.c

	src/core/main.c
)

list(APPEND SourceFiles
	${CoreSources}
	${GameSources}
)

add_executable(${APPNAME} ${SourceFiles})
target_link_libraries(${APPNAME} SDL2 SDL2main SDL2_image SDL2_mixer m)
#add_custom_command(TARGET ${APPNAME} POST_BUILD COMMAND ${APPNAME} WORKING_DIRECTORY ${PROJECT_SOURCE_DIR})
