add_executable(ViewTest
  ModelMock.cpp
  ViewTest.cpp
  ViewTest.qrc
)
target_link_libraries(ViewTest DrAutomatonMock)
