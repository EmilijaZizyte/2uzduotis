#include "pch.h"
#include "gtest/gtest.h"
#include "C:\\Users\\computer\\Desktop\\v2.0\\v2.0\\studentas.h"
#include "C:\\Users\\computer\\Desktop\\v2.0\\v2.0\\zmogus.h"

TEST(MedianaTest, OddNumberOfElements) {
    std::vector<int> v = { 3, 1, 5 };
    EXPECT_EQ(mediana(v), 3); 
}

TEST(MedianaTest, EvenNumberOfElements) {
    std::vector<int> v = { 4, 2, 6, 8 };
    EXPECT_EQ(mediana(v), 5); 
}

TEST(MedianaTest, SingleElement) {
    std::vector<int> v = { 10 };
    EXPECT_EQ(mediana(v), 10); 
}

// ---- STUDENTAS TESTS ----

TEST(StudentasTest, KonstruktoriaiIrGetteriai) {
    // ---- Test default constructor ----
    Studentas s1;
    EXPECT_EQ(s1.getVard(), "");          // default name
    EXPECT_EQ(s1.getPav(), "");           // default surname
    EXPECT_EQ(s1.getPaz().size(), 0);     // no grades
    EXPECT_EQ(s1.getEgzas(), 0);          // default exam
    EXPECT_DOUBLE_EQ(s1.getRezVid(), 0.0);// default result
    EXPECT_DOUBLE_EQ(s1.getRezMed(), 0.0);// default result

    // ---- Test default constructor + setters ----
    Studentas s2;
    s2.setVard("Jonas");
    s2.setPav("Jonaitis");
    std::vector<int> nd2 = { 8, 9, 10 };
    s2.setPazymiai(nd2);
    s2.setEgzas(9);
    s2.setRezVid(8.5);
    s2.setRezMed(9.0);

    EXPECT_EQ(s2.getVard(), "Jonas");
    EXPECT_EQ(s2.getPav(), "Jonaitis");
    EXPECT_EQ(s2.getPaz(), nd2);
    EXPECT_EQ(s2.getEgzas(), 9);
    EXPECT_DOUBLE_EQ(s2.getRezVid(), 8.5);
    EXPECT_DOUBLE_EQ(s2.getRezMed(), 9.0);

    // ---- Test 4-parameter constructor (vector + exam) ----
    std::vector<int> nd3 = { 7, 8, 9 };
    Studentas s3("Petras", "Petraitis", nd3, 10);

    EXPECT_EQ(s3.getVard(), "Petras");
    EXPECT_EQ(s3.getPav(), "Petraitis");
    EXPECT_EQ(s3.getPaz(), nd3);
    EXPECT_EQ(s3.getEgzas(), 10);
    EXPECT_DOUBLE_EQ(s3.getRezVid(), 0.0); 
    EXPECT_DOUBLE_EQ(s3.getRezMed(), 0.0); 
}


TEST(StudentasTest, CopyKonstruktorius) {
    std::vector<int> nd = { 7 };
    Studentas s1("Ona", "Onaitė", nd, 10);
    Studentas s2(s1);

    EXPECT_EQ(s2.getVard(), "Ona");
    EXPECT_EQ(s2.getPav(), "Onaitė");
    EXPECT_EQ(s2.getPaz(), nd);
    EXPECT_EQ(s2.getEgzas(), 10);
    EXPECT_DOUBLE_EQ(s2.getRezVid(), 0.0); 
    EXPECT_DOUBLE_EQ(s2.getRezMed(), 0.0); 
}



// ---- MAIN ----

int main(int argc, char** argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
