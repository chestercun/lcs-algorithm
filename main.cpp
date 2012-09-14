#include <iostream>
#include <algorithm>
#include <fstream>

#include <time.h>
#include "LCSS.h"

int LCSS2 (std::string const & a, std::string const & b)
{
	// scratch array
	int Matrix[1001][1001];

	// initialization
	for (unsigned int i=0; i<=a.size(); i++)
	{
		Matrix[i][0] = 0;
	}
	for (unsigned int j=0; j<=b.size(); j++)
	{
		Matrix[0][j] = 0;
	}

	// main algorithm
	for (unsigned int i=0; i<a.size(); i++)
	{
		for (unsigned int j=0; j<b.size(); j++)
		{
			if (a[i] == b[j])
			{
				Matrix[i+1][j+1] = Matrix[i][j] + 1;
			}
			else
			{
				Matrix[i+1][j+1] = std::max(Matrix[i+1][j], Matrix[i][j+1]);
			}
		}
	}
	return Matrix[a.size()][b.size()];
}

void TestClasses(std::string const & a, std::string const & b)
{
	clock_t start, finish;

	LCSS Test (a,b);
	std::cout << "LCSS for " << a << " and " << b;

	// Timing
	start = clock();
	int length = Test.LongestSubsequence();
	finish = clock();

	std:: cout << "\nHas length: " << length;

	std::cout << "\nTime taken: " << ((double)(finish-start))/CLOCKS_PER_SEC << " seconds.\n\n";
}

void TestClasses2(std::string const & a, std::string const & b)
{
	clock_t start, finish;

	std::cout << "LCSS v2 for " << a << " and " << b;

	// Timing
	start = clock();

	int length = LCSS2(a,b);

	finish = clock();

	std:: cout << "\nHas length: " << length;

	std::cout << "\nTime taken: " << ((double)(finish-start))/CLOCKS_PER_SEC << " seconds.\n\n";
}


int main(int argc, char* argv[])
{
	// Longest increasing integer subsequence approach
	TestClasses("Rensselaer","Rearend");
	TestClasses("abaabababbabaabbab","aababbbbaabbabba");
	TestClasses("Chester Cun col","Ciehaeitowsooiteoijr Cun! is nobody cool");
	TestClasses("Cheesecake","Cheeeaeeeesecaaaaaaake");
	TestClasses("axedietheperson","xdtapso");

	std::cout << "\n\n\n\n";

	// 2D Array Approach
	TestClasses2("Rensselaer","Rearend");
	TestClasses2("abaabababbabaabbab","aababbbbaabbabba");
	TestClasses2("Chester Cun col","Ciehaeitowsooiteoijr Cun! is nobody cool");
	TestClasses2("Cheesecake","Cheeeaeeeesecaaaaaaake");
	TestClasses2("axedietheperson","xdtapso");

	std::cout << "\n\n\n\n";

	
	/*std::ofstream outfile(argv[1]);
	int rsize=200;
	for (int i=0; i<rsize;)
	{
		int j = std::rand() % 127;
		if ((j>=65 && j<=90)||(j>=97 && j<=122))
		{
			outfile << (char) j;
			i++;
		}
	}
	outfile << "\n";
	for (int i=0; i<rsize;)
	{
		int j = std::rand() % 127;
		if ((j>=65 && j<=90)||(j>=97 && j<=122))
		{
			outfile << (char) j;
			i++;
		}
	}
	outfile.close();*/


	/*std::ifstream infile (argv[1]);
	std::string BigString1, BigString2;

	infile >> BigString1 >> BigString2;

	infile.close();

	TestClasses(BigString1,BigString2);
	TestClasses2(BigString1,BigString2);*/

	TestClasses("a1b2c3d4e","zz1yy2xx3ww4vv");
	TestClasses2("a1b2c3d4e","zz1yy2xx3ww4vv");
	TestClasses("abcdgh","aedfhr");
	TestClasses2("abcdgh","aedfhr");
	TestClasses("abcdefghijklmnopqrstuvwxyz","a0b0c0d0e0f0g0h0i0j0k0l0m0n0o0p0q0r0s0t0u0v0w0x0y0z0");
	TestClasses2("abcdefghijklmnopqrstuvwxyz","a0b0c0d0e0f0g0h0i0j0k0l0m0n0o0p0q0r0s0t0u0v0w0x0y0z0");
	TestClasses("abcdefghijklmnzyxwvutsrqpo","opqrstuvwxyzabcdefghijklmn");
	TestClasses2("abcdefghijklmnzyxwvutsrqpo","opqrstuvwxyzabcdefghijklmn");

	std::cout << "\n\n";
	return 0;
}

