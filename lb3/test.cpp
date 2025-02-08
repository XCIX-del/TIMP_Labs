#include <iostream>
#include <UnitTest++/UnitTest++.h>
#include "includer.h"
#include <locale>
struct KeyB_fixture {
    modAlphaCipher * p;
    KeyB_fixture()
    {
        p = new modAlphaCipher;
        p->start(L"В");
    }
    ~KeyB_fixture()
    {
        delete p;
    }
};

SUITE(modAlpha_test)
{
    SUITE(KeyTest) {
        TEST(ValidKey) {
            modAlphaCipher cipher;
            std::wstring temp = L"АБВАБ";
            cipher.start(cipher.key_validation(L"АБВ",temp));
            std::wstring res = cipher.encrypt(L"ААААА");
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
            
        }
     TEST(LongKey) {
            modAlphaCipher cipher;
            std::wstring temp = L"АБВГД";
            cipher.start(cipher.key_validation(L"АБВГДЕЁЖЗИ",temp));
            std::wstring res = cipher.encrypt(L"ААААА");
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST(LowCaseKey) {
            modAlphaCipher cipher;
            std::wstring temp = L"БВГБВ";
            cipher.start(cipher.key_validation(L"бвг",temp));
            std::wstring res = cipher.encrypt(L"ААААА");
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST(DigitsInKey) {
            modAlphaCipher cipher;
            const std::wstring temp1=L"ААААА";
            std::wstring temp=L"Б1";
            CHECK_THROW(cipher.start(cipher.key_validation(temp,temp1)),cipher_error);
        }
        TEST(PunctuationInKey) {
            modAlphaCipher cipher;
            const std::wstring temp1=L"ААААА";
            std::wstring temp=L"Б,Г";
            CHECK_THROW(cipher.start(cipher.key_validation(temp,temp1)),cipher_error);
        }
        TEST(WhitespaceInKey) {
            modAlphaCipher cipher;
            const std::wstring temp1=L"ААААА";
            std::wstring temp=L"Б Г";
            CHECK_THROW(cipher.start(cipher.key_validation(temp,temp1)),cipher_error);
        }
        TEST(EmptyKey) {
            modAlphaCipher cipher;
            const std::wstring temp1=L"ААААА";
            std::wstring temp=L"";
            CHECK_THROW(cipher.start(cipher.key_validation(temp,temp1)),cipher_error);
        }
        TEST(WeakKey) {
            modAlphaCipher cipher;
            const std::wstring temp1=L"СТРОКАДЛЯТЕСТА";
            std::wstring temp=L"ААА";
            CHECK_THROW(cipher.start(cipher.key_validation(temp,temp1)),cipher_error);
        }
        TEST(KeyFromWrongAlphabet) {
            modAlphaCipher cipher;
            const std::wstring temp1=L"ААААА";
            std::wstring temp=L"ABC";
            CHECK_THROW(cipher.start(cipher.key_validation(temp,temp1)),cipher_error);
        }
    }
    SUITE(EncryptTest) {
        TEST_FIXTURE(KeyB_fixture, UpCaseString) {
            std::wstring res = p->encrypt(L"ВЧАЩАХЮГАЖИЛБЫЦИТРУСДАНОФАЛЬШИВЫЙЭКЗЕМПЛЯР");
            std::wstring temp = L"ДЩВЫВЧАЕВИКНГЭШКФТХУЁВПРЦВНЮЪКДЭЛЯМЙЖОСНБТ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, LowCaseString) {
            std::wstring res = p->encrypt(L"вчащахюгажилбылцитрусданофальшивыйэкземпляр") ;
            std::wstring temp = L"ДЩВЫВЧАЕВИКНГЭНШКФТХУЁВПРЦВНЮЪКДЭЛЯМЙЖОСНБТ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, StringWithWhitspaceAndPunct) {
            std::wstring res = p->encrypt(L"В ЧАЩАХ ЮГА ЖИЛ БЫ ЦИТРУС, ДА НО ФАЛЬШИВЫЙ ЭКЗЕМПЛЯР") ;
            std::wstring temp = L"ДЩВЫВЧАЕВИКНГЭШКФТХУЁВПРЦВНЮЪКДЭЛЯМЙЖОСНБТ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, StringWithNumbers) {
            std::wstring res = p->encrypt(L"МНЕНЕДАВНОИСПОЛНИЛОСЬ18");
            std::wstring temp = L"ОПЖПЖЁВДПРКУСРНПКНРУЮ";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, EmptyString) {
            CHECK_THROW(p->encrypt(L""),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, NoAlphaString) {
            CHECK_THROW(p->encrypt(L"1234+8765=9999"),cipher_error);
        }
        TEST(MaxShiftKey) {
            modAlphaCipher cipher;
            cipher.start(L"Я");
            std::wstring res = cipher.encrypt(L"ВЧАЩАХЮГАЖИЛБЫЦИТРУСДАНОФАЛЬШИВЫЙЭКЗЕМЛЯР");
            std::wstring temp = L"БЦЯШЯФЭВЯЁЗКАЪХЗСПТРГЯМНУЯКЫЧЗБЪИЬЙЖДЛКЮП";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture,EnglishString) {
            CHECK_THROW(p->encrypt(L"ENGLISHTEXT"),cipher_error);
        }
    }
    SUITE(DecryptText) {
        TEST_FIXTURE(KeyB_fixture, UpCaseString) {
            std::wstring res = p->decrypt(L"ДЩВЫВЧАЕВИКНГЭШКФТХУЁВПРЦВНЮЪКДЭЛЯМЙЖОСНБТ") ;
            std::wstring temp = L"ВЧАЩАХЮГАЖИЛБЫЦИТРУСДАНОФАЛЬШИВЫЙЭКЗЕМПЛЯР";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture, LowCaseString) {
            CHECK_THROW(p->decrypt(L"дщвывчаевикнгэшкфтхуёвпрцвнюъкдэлямйжоснбт"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, WhitespaceString) {
            CHECK_THROW(p->decrypt(L"дщвыв чаевикнгэшк фтхуёвпрцвнюъкд элямйжоснбт"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, DigitsString) {
            CHECK_THROW(p->decrypt(L"ОПЖПЖЁВДПРКУСРНПКНРУЮ18"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, PunctString) {
            CHECK_THROW(p->decrypt(L"ДЩВЫВЧАЕВИКНГЭШКФТХУЁВ,ПРЦВНЮЪКДЭЛЯМЙЖОНБТ"),cipher_error);
        }
        TEST_FIXTURE(KeyB_fixture, EmptyString) {
            CHECK_THROW(p->decrypt(L""),cipher_error);
        }
        TEST(MaxShiftKey) {
            modAlphaCipher cipher;
            cipher.start(L"Я");
            std::wstring res = cipher.decrypt(L"БЦЯШЯФЭВЯЁЗКАЪХЗСПТРГЯМНУЯКЫЧЗБЪИЬЙЖДЛКЮП") ;
            std::wstring temp = L"ВЧАЩАХЮГАЖИЛБЫЦИТРУСДАНОФАЛЬШИВЫЙЭКЗЕМЛЯР";
            if(temp==res){
                CHECK(true);
            }
            else{
                CHECK(false);
            }
        }
        TEST_FIXTURE(KeyB_fixture,EnglishString) {
            CHECK_THROW(p->encrypt(L"ASDGFDHRTWSFD"),cipher_error);
        }
    }
}
SUITE(table_cipher_test){
    SUITE(initialization_test){
        TEST(right_key){
            std::string test = "iamstudent";
            CHECK_THROW(table_cipher t (test,5),table_cipher_error);
        }
        TEST(long_key){
            std::string test = "iamstudent";
            CHECK_THROW(table_cipher t (test,12),table_cipher_error);
        }
        TEST(short_key){
            std::string test = "iamstudent";
            CHECK_THROW(table_cipher t (test,1),table_cipher_error);
        }
        TEST(minimal_key){
            std::string test = "iamstudent";
            table_cipher t (test,2);
            CHECK_EQUAL("ASUETIMTDN",t.encrypt());
        }
        TEST(wrong_key){
            std::string test = "iamstudent";
            CHECK_THROW(table_cipher t (test,'test'),table_cipher_error);
        }
        TEST(text_with_spaces){
            std::string test = "i am student";
            CHECK_THROW(table_cipher t (test,5),table_cipher_error);
        }
        TEST(text_with_spsymbols){
            std::string test = "iamstudent!@#$";
            CHECK_THROW(table_cipher t (test,5),table_cipher_error);
        }
        TEST(text_with_numbers){
            std::string test = "iamstudent123";
            CHECK_THROW(table_cipher t (test,5),table_cipher_error);
        }
    }
    SUITE(encrypt_test){
        TEST(no_text){
            std::string test = "";
            CHECK_THROW(table_cipher t (test,5),table_cipher_error);
        }
        TEST(upcase_text){
            std::string test = "IAMSTUDENT";
            table_cipher t (test,5);
            CHECK_EQUAL("TTSNMEADIU",t.encrypt());
        }
        TEST(lowcase_text){
            std::string test = "iamstudent";
            table_cipher t (test,5);
            CHECK_EQUAL("TTSNMEADIU",t.encrypt());
        }
        TEST(long_text){
            std::string test = "IAMSTUDENTIAMSTUDENTIAMSTUDENT";
            table_cipher t (test,5);
            CHECK_EQUAL("TTTTTTSNSNSNMEMEMEADADADIUIUIU",t.encrypt());
        }
        TEST(text_with_spaces){
            std::string test = "I AM STUDENT";
            table_cipher t (test,5);
            CHECK_EQUAL("TTSNMEADIU",t.encrypt());
        }
        TEST(non_int_key){
            std::string test = "IAMSTUDENT";
            table_cipher t (test,5.9);
            CHECK_EQUAL("TTSNMEADIU",t.encrypt());
        }
    }
    SUITE(decrypt_test){
        TEST(upcase_text){
            std::string test = "TTSNMEADIU";
            table_cipher t (test,5);
            CHECK_EQUAL("IAMSTUDENT",t.decrypt());
        }
        TEST(lowcase_text){
            std::string test = "ttsnmeadiu";
            table_cipher t (test,5);
            CHECK_EQUAL("IAMSTUDENT",t.decrypt());
        }
        TEST(long_text){
            std::string test = "TTTTTTSNSNSNMEMEMEADADADIUIUIU";
            table_cipher t (test,5);
            CHECK_EQUAL("IAMSTUDENTIAMSTUDENTIAMSTUDENT",t.decrypt());
        }
        TEST(text_with_spaces){
            std::string test = "T TS NMEADIU";
            table_cipher t (test,5);
            CHECK_EQUAL("IAMSTUDENT",t.decrypt());
        }
        TEST(non_int_key){
            std::string test = "TTSNMEADIU";
            table_cipher t (test,5.9);
            CHECK_EQUAL("IAMSTUDENT",t.decrypt());
        }
    }
}
int main(){
    std::locale loc("ru_RU.UTF-8");
    std::locale::global(loc);
    return UnitTest::RunAllTests();
}
