#include "pch.h"
#include "CppUnitTest.h"
#include "core.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest1
{
	TEST_CLASS(UnitTest1)
	{
	public:
		
		TEST_METHOD(TestMethod1)
		{
			char * words[101] = {"alacdcdvra", "aavdawe", "zoo", "elepcveant", "unwewcr",
                               "fadvx", "davcdfg", "mcen", "lwfjuioef", "tasdcbniak",
                               "pseudopseudohypopaacvdrathyroidism"};
			char* answer[101];
			for (int i = 0; i < 101; i++) {
				answer[i] = (char*)malloc(sizeof(char) * 601);
			}

			int l = gen_chain_word(words, 11, answer, 'a', 0, false);

			Assert::AreEqual(l, 4);
			Assert::AreEqual("alacdcdvra", answer[0]);
			Assert::AreEqual("aavdawe", answer[1]);
			Assert::AreEqual("elepcveant", answer[2]);
			Assert::AreEqual("tasdcbniak", answer[3]);
			for (int i = 0; i < 101; i++) {
				free(answer[i]);
			}
		}

		TEST_METHOD(TestMethod2) {
                  char* words[101] = {"awiubd",
                                      "cndfjkv",
                                      "cdnjk",
                                      "vifdvujba",
                                      "ceuincb",
                                      "cdfjvna",
                                      "cdca", "cnierin", "creij", "jcsde","esof", "fnskjb"};
                  char* answer[101];
                  for (int i = 0; i < 101; i++) {
                    answer[i] = (char*)malloc(sizeof(char) * 601);
                  }

                  int l = gen_chains_all(words, 12, answer);

                  Assert::AreEqual(l, 11);
                  Assert::AreEqual("cndfjkv vifdvujba", answer[0]);
                  Assert::AreEqual("cndfjkv vifdvujba awiubd", answer[1]);
                  Assert::AreEqual("vifdvujba awiubd", answer[2]);
                  Assert::AreEqual("cdfjvna awiubd", answer[3]);
                  Assert::AreEqual("cdca awiubd", answer[4]);
                  Assert::AreEqual("creij jcsde", answer[5]);
                  Assert::AreEqual("creij jcsde esof", answer[6]);
                  Assert::AreEqual("creij jcsde esof fnskjb", answer[7]);
                  Assert::AreEqual("jcsde esof", answer[8]);
                  Assert::AreEqual("jcsde esof fnskjb", answer[9]);
                  Assert::AreEqual("esof fnskjb", answer[10]);
                  for (int i = 0; i < 101; i++) {
                    free(answer[i]);
                  }
		}

        TEST_METHOD(TestMethod3) {
                  char* words[101] = {"awiubd",    "cndfjkv", "cdnjk",
                                      "vifdvujba", "ceuincb", "cdfjvna",
                                      "cdca",      "cnierin", "creij",
                                      "jcsde",     "esof",    "fnskjb"};
                  char* answer[101];
                  for (int i = 0; i < 101; i++) {
                    answer[i] = (char*)malloc(sizeof(char) * 601);
                  }

                  int l = gen_chain_word_unique(words, 12, answer);

                  Assert::AreEqual(l, 4);
                  Assert::AreEqual("creij", answer[0]);
                  Assert::AreEqual("jcsde", answer[1]);
                  Assert::AreEqual("esof", answer[2]);
                  Assert::AreEqual("fnskjb", answer[3]);
                  for (int i = 0; i < 101; i++) {
                    free(answer[i]);
                  }
                }
        TEST_METHOD(TestMethod4) {
          char* words[101] = {"awiubd",  "cndfjkv", "cdnjk", "vifdvujba",
                              "ceuincb", "cdfjvna", "cdca",  "cnierin",
                              "creij",   "jcsde",   "esof",  "fnskjb"};
          char* answer[101];
          for (int i = 0; i < 101; i++) {
            answer[i] = (char*)malloc(sizeof(char) * 601);
          }

          int l = gen_chain_char(words, 12, answer, 0, 0, false);

          Assert::AreEqual(l, 22);
          Assert::AreEqual("cndfjkv", answer[0]);
          Assert::AreEqual("vifdvujba", answer[1]);
          Assert::AreEqual("awiubd", answer[2]);
          for (int i = 0; i < 101; i++) {
            free(answer[i]);
          }
        }

        TEST_METHOD(TestMethod5) {
          char* words[101] = {"awiubd",  "cndfjkv", "cdnjk", "vifdvujba",
                              "ceuincb", "cdfjvna", "cdca",  "cnierin",
                              "creij",   "jcsde",   "esof",  "fnskjb",
                              "afudfshna", "cda",     "vdasv",      "feqaf",
                              "fdav",          "aaeer",        "vadvc",      "aefv"};
          char* answer[101];
          for (int i = 0; i < 101; i++) {
            answer[i] = (char*)malloc(sizeof(char) * 601);
          }

          int l = gen_chain_char(words, 20, answer, 0, 0, true);

          Assert::AreEqual(l, 68);
          Assert::AreEqual("cdfjvna", answer[0]);
          Assert::AreEqual("afudfshna", answer[1]);
          Assert::AreEqual("aefv", answer[2]);
          Assert::AreEqual("vdasv", answer[3]);
          Assert::AreEqual("vadvc", answer[4]);
          Assert::AreEqual("creij", answer[5]);
          Assert::AreEqual("jcsde", answer[6]);
          Assert::AreEqual("esof", answer[7]);
          Assert::AreEqual("feqaf", answer[8]);
          Assert::AreEqual("fdav", answer[9]);
          Assert::AreEqual("vifdvujba", answer[10]);
          Assert::AreEqual("awiubd", answer[11]);
          for (int i = 0; i < 101; i++) {
            free(answer[i]);
          }
        }

        TEST_METHOD(TestMethod6) {
          char* words[101] = {"aiegienk",    "ebueba",        "esof",
                              "fbdfbueegds", "fifwofoahwfsw", "fnskjb",
                              "jcsde",       "jfegegiu",      "sfwffdfwsc",
                              "ufyfefna",    "wfdifehgu"};
          char* answer[101];
          for (int i = 0; i < 101; i++) {
            answer[i] = (char*)malloc(sizeof(char) * 601);
          }

          int len = gen_chain_word(words, 11, answer, 0, 'k', false);

          Assert::AreEqual(len, 6);
          Assert::AreEqual("jcsde", answer[0]);
          Assert::AreEqual("esof", answer[1]);
          Assert::AreEqual("fifwofoahwfsw", answer[2]);
          Assert::AreEqual("wfdifehgu", answer[3]);
          Assert::AreEqual("ufyfefna", answer[4]);
          Assert::AreEqual("aiegienk", answer[5]);

          for (int i = 0; i < 101; i++) {
            free(answer[i]);
          }
        }

        TEST_METHOD(TestMethod7) {
          char* words[101] = {
              "aavdawe",        "alacdcdvra",
              "dAVCdfg",        "edahfwofa",
              "elepcveant",     "fadvx",
              "fsfiheufge",     "lwfjuioef",
              "Mcen",           "pseudopseudohypopaacvdrathyroidism",
              "tasdcbniak",     "unwewcr",
              "wudisgeggegsge", "zoo"};
          char* answer[101];
          for (int i = 0; i < 101; i++) {
            answer[i] = (char*)malloc(sizeof(char) * 601);
          }

          int len = gen_chain_word(words, 14, answer, 0, 0, true);

          Assert::AreEqual(len, 7);
          Assert::AreEqual("lwfjuioef", answer[0]);
          Assert::AreEqual("fsfiheufge", answer[1]);
          Assert::AreEqual("edahfwofa", answer[2]);
          Assert::AreEqual("alacdcdvra", answer[3]);
          Assert::AreEqual("aavdawe", answer[4]);
          Assert::AreEqual("elepcveant", answer[5]);
          Assert::AreEqual("tasdcbniak", answer[6]);

          for (int i = 0; i < 101; i++) {
            free(answer[i]);
          }
        }

        TEST_METHOD(TestMethod8) {
          char* words[101] = {
              "aavdawe",    "alacdcdvra", "davcdfg",
              "elepcveant", "faCvx",      "fsfiheufge",
              "lwfjuioef",  "mcen",       "pseudopseudohypopaacvdrathyroidism",
              "tasdcbniak", "unwewcr",    "wudisgeggegsge",
              "zoo"};
          char* answer[101];
          for (int i = 0; i < 101; i++) {
            answer[i] = (char*)malloc(sizeof(char) * 601);
          }

          int len = gen_chain_char(words, 13, answer, 'f', 0, false);

          Assert::AreEqual(len, 30);
          Assert::AreEqual("fsfiheufge", answer[0]);
          Assert::AreEqual("elepcveant", answer[1]);
          Assert::AreEqual("tasdcbniak", answer[2]);

          for (int i = 0; i < 101; i++) {
            free(answer[i]);
          }
        }

        TEST_METHOD(TestMethod9) {
          char* words[101] = {
              "aavdawe",    "alacdcdvra", "davcdfg",
              "elepcveant", "fadvx",      "fsfiheufge",
              "lwfjuioef",  "mcen",       "pseudopAAAAAAAAAopaacvdrathyroidism",
              "tasdcbniak", "unwewcr",    "wudisgeggegsge",
              "zoo"};
          char* answer[101];
          for (int i = 0; i < 101; i++) {
            answer[i] = (char*)malloc(sizeof(char) * 601);
          }

          int len = gen_chain_char(words, 13, answer, 0, 'k', false);

          Assert::AreEqual(len, 39);
          Assert::AreEqual("lwfjuioef", answer[0]);
          Assert::AreEqual("fsfiheufge", answer[1]);
          Assert::AreEqual("elepcveant", answer[2]);
          Assert::AreEqual("tasdcbniak", answer[3]);

          for (int i = 0; i < 101; i++) {
            free(answer[i]);
          }
        }
	};
}
