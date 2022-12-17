cmake_minimum_required(VERSION 3.16)
project(lab_2)

set(CMAKE_CXX_STANDARD 14)

add_executable(lab_2 main.cpp strategy.h simulator.cpp simulator.h factory.cpp factory.h strategies/simple/alwayscooperate.cpp strategies/simple/alwayscooperate.h strategies/simple/alwaysdefect.cpp strategies/simple/alwaysdefect.h strategies/simple/alwaysalternateaction.cpp strategies/simple/alwaysalternateaction.h strategies/complex/mostusedaction.cpp strategies/complex/mostusedaction.h strategies/complex/defectifanydefect.cpp strategies/complex/defectifanydefect.h types.h exceptions.h gamemodes/competitionnodetails.cpp gamemodes/competitionnodetails.h gamemode.h gamemodes/competitionwithdetails.cpp gamemodes/competitionwithdetails.h gamemodes/tournament.cpp gamemodes/tournament.h cmdparser.cpp cmdparser.h strategies/simple/randomaction.cpp strategies/simple/randomaction.h strategies/complex/mostusedactionwithforgiveness.cpp strategies/complex/mostusedactionwithforgiveness.h)
