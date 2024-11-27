#include "pch.h"
#include "CppUnitTest.h"
#include <fstream>
#include "../lab12.1/lab12.1.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace UnitTest2
{
	TEST_CLASS(UnitTest2)
	{
	public:
		TEST_METHOD(TestMethod1)
		{
			char inputFile[] = "test_input.bin";
			char outputFile[] = "test_output.bin";

			// Створення вхідного бінарного файлу
			{
				ofstream fout(inputFile, ios::binary);
				double testData[] = { -5.0, 3.2, -1.1, 7.8, 0.0 };
				for (double num : testData) {
					fout.write((char*)&num, sizeof(num));
				}
			}

			// Виклик функції обробки ProcessBIN
			ProcessBIN(inputFile, outputFile);

			// Перевірка вихідного файлу
			ifstream fin(outputFile, ios::binary);
			Assert::IsTrue(fin.is_open(), L"Output file was not created!");

			// Зчитування та перевірка результатів
			double avgNegative, avgPositive;

			fin.read((char*)&avgNegative, sizeof(avgNegative));
			fin.read((char*)&avgPositive, sizeof(avgPositive));

			// Розрахунок очікуваних результатів
			double expectedAvgNegative = (-5.0 + -1.1) / 2; // середнє арифметичне від'ємних
			double expectedAvgPositive = (3.2 + 7.8) / 2;   // середнє арифметичне додатних

			Assert::AreEqual(expectedAvgNegative, avgNegative, 0.01, L"Average negative number incorrect");
			Assert::AreEqual(expectedAvgPositive, avgPositive, 0.01, L"Average positive number incorrect");
		}
	};
}
