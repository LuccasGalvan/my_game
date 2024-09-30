cmake_minimum_required(VERSION 3.29)
project(RPGGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(RPGGame main.cpp
        headers/types.h
        statblock.cpp
        headers/statblock.h
        corestats.cpp
        headers/corestats.h
        buff.cpp
        headers/buff.h
        pointwell.cpp
        headers/pointwell.h
        ability.cpp
        headers/ability.h
        item.cpp
        headers/item.h
        itemFactory.cpp
        headers/itemFactory.h
        playerCharacter.cpp
        headers/playerCharacter.h)
