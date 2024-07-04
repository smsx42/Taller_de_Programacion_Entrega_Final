#include <gtest/gtest.h>
#include "../src/server_src/rectangulo.h"



const uint32_t id_bala = 00;
const uint32_t id_jugador = 00;
const uint32_t posx = 0;
const uint32_t posy = 0;

struct RectanguloTest : testing::Test{
    Rectangulo * rectangulo1;
    Rectangulo * rectangulo2;
    Rectangulo * rectangulo3;

    RectanguloTest(){
        rectangulo1 = new Rectangulo(0,0,10,10);
        rectangulo2 = new Rectangulo(5,5,10,10);
        rectangulo3 = new Rectangulo(20,20,10,10);
    }

    ~RectanguloTest(){
        delete rectangulo1;
        delete rectangulo2;
        delete rectangulo3;
    }
};

TEST_F(RectanguloTest, MismoRectanguloHayColision){
    EXPECT_EQ(rectangulo1->hay_colision(*rectangulo1), true);
}
TEST_F(RectanguloTest, RectangulosSeSuperponenHayColision){
    EXPECT_EQ(rectangulo1->hay_colision(*rectangulo2), true);
}
TEST_F(RectanguloTest, RectangulosNoSeSuperponenNoHayColision){
    EXPECT_EQ(rectangulo1->hay_colision(*rectangulo3), false);
}
TEST_F(RectanguloTest, RectangulosSeSuperponenEnXHayColision){
    EXPECT_EQ(rectangulo1->hay_colision_x(*rectangulo2), true);
}
TEST_F(RectanguloTest, RectangulosNoSeSuperponenEnXNoHayColision){
    EXPECT_EQ(rectangulo1->hay_colision_x(*rectangulo3), false);
}
TEST_F(RectanguloTest, RectangulosSeSuperponenEnYHayColision){
    EXPECT_EQ(rectangulo1->hay_colision_y(*rectangulo2), true);
}
TEST_F(RectanguloTest, RectangulosNoSeSuperponenEnYNoHayColision){
    EXPECT_EQ(rectangulo1->hay_colision_y(*rectangulo3), false);
}

int main(int argc, char*argv[]){
    std::cout << "-----------------------------------------" << std::endl;
    std::cout << "\nTests Rectangulo\n" << std::endl;
    std::cout << "-----------------------------------------" << std::endl;    
    testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}