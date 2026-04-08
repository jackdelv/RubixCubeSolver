add_library(RubixCube)

target_sources(RubixCube
            PRIVATE
                rubixCube.cpp
            PUBLIC
                FILE_SET HEADERS
                FILES
                    rubixCube.hpp)

add_executable(Engine)

target_sources(Engine
            PRIVATE
                engine.cpp
)

target_link_libraries(Engine RubixCube)