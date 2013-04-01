cmake_minimum_required (VERSION 2.8)
set(CMAKE_CXX_FLAGS "-g -Wall")

project (Caylus CXX)

# The version number.
set (Caylus_VERSION_MAJOR 1)
set (Caylus_VERSION_MINOR 0)

# Directories
set (CAYLUS_SOURCE_DIR "src")
set (CAYLUS_BINARY_DIR "bin")
set (Caylus_IMAGE_DIR "share/img")

# configure a header file to pass some of the CMake settings
# to the source code
configure_file (
  "${CAYLUS_SOURCE_DIR}/CaylusConfig.h.in"
  "${CAYLUS_SOURCE_DIR}/CaylusConfig.h"
  )

# add the binary tree to the search path for include files
# so that we will find CaylusConfig.h
include_directories ("${CAYLUS_SOURCE_DIR}")

# Define sources and executable
set (EXECUTABLE_NAME "Caylus")
add_executable (${EXECUTABLE_NAME} "${CAYLUS_SOURCE_DIR}/main.cc")

# Subdirectories
add_subdirectory ("${CAYLUS_SOURCE_DIR}/controller")
target_link_libraries (${EXECUTABLE_NAME} Caylus_Controller)

add_subdirectory ("${CAYLUS_SOURCE_DIR}/view")
target_link_libraries (${EXECUTABLE_NAME} Caylus_View)

# External libs
find_package (Boost REQUIRED thread signals)
target_link_libraries (${EXECUTABLE_NAME} ${Boost_LIBRARIES})

# Install target
install(TARGETS ${EXECUTABLE_NAME} DESTINATION ${CAYLUS_BINARY_DIR})

enable_testing()

add_test(GateWithWorkerOnCastle ./Caylus -d test/buildings/gate/one_worker_on_castle)
add_test(GateWithWorkerOnInn ./Caylus -d test/buildings/gate/one_worker_on_inn)
add_test(GateWithWorkerOnStables ./Caylus -d test/buildings/gate/one_worker_on_stables)
add_test(GateWithBridgeChoice ./Caylus -d test/buildings/gate/bridge_choice)
add_test(TradingPost ./Caylus -d test/buildings/trading_post)
add_test(MerchantGuild ./Caylus -d test/buildings/merchant_guild)
add_test(JoustFieldNotEnoughResource ./Caylus -d test/buildings/joust_field/not_enough_resource)
add_test(JoustFieldEnoughResource ./Caylus -d test/buildings/joust_field/enough_resource)
add_test(StablesWithTwoPlayers ./Caylus -d test/buildings/stables/two_players)
add_test(StablesWithThreePlayers ./Caylus -d test/buildings/stables/three_players)
add_test(StablesWithFourPlayers ./Caylus -d test/buildings/stables/four_players)
add_test(Inn ./Caylus -d test/buildings/inn)
add_test(NeutralFarm ./Caylus -d test/buildings/neutral_farm)
add_test(NeutralSawmill ./Caylus -d test/buildings/neutral_sawmill)

add_test(CastleOnlyOneWorker ./Caylus -d test/castle/only_one_worker)
