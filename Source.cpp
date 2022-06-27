#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <fstream>

using namespace std;

string graycode[16] = { "0000", "0001", "0011", "0010", "0100", "0101", "0111", "0110", "1100",
					   "1101", "1111", "1110", "1000", "1001", "1011", "1010" };

string binary[16] = { "0000", "0001", "0010", "0011", "0100", "0101", "0110", "0111", "1000",
					   "1001", "1010", "1011", "1100", "1101", "1110", "1111" };

int term[16] = { 0, 1, 3, 2, 4, 5, 7, 6, 12, 13, 15, 14, 8, 9, 11, 10 };

struct imp1
{
	vector <int> term;
	string code;
	bool min = false;
};

bool sort(int& a, int& b)
{
	return a < b;
}

bool sort1(imp1& a, imp1& b)
{
	return a.term[0] < b.term[0];
}

bool sort2(imp1& a, imp1& b)
{
	return a.term[0] < b.term[0];
}

bool sort3(imp1& a, imp1& b)
{
	return a.term[0] < b.term[0];
}

bool sort4(imp1& a, imp1& b)
{
	return a.term[0] < b.term[0];
}

bool sortans(string& a, string& b)
{
	return a > b;
}

string newcode(string& str1, string& str2)
{
	string temp = str1;

	for (int i = 0; i < 4; i++)
	{
		if (str1[i] != str2[i])
		{
			temp[i] = '-';
		}
	}

	return temp;
}

int bits(string& str1, string& str2)
{
	int sum = 0;

	for (int i = 0; i < 4; i++)
	{
		if (str1[i] != str2[i])
		{
			sum++;
		}
	}

	return sum;
}

bool non(vector <int>& match)
{
	for (int i = 0; i < match.size(); i++)
	{
		if (match[i] != 0)
		{
			return false;
		}
	}

	return true;
}

bool keepfind(bool* one)
{
	for (int i = 0; i < 16; i++)
	{
		if (one[i] == true)
		{
			return true;
		}
	}

	return false;
}

int main()
{
	ifstream infile;
	infile.open("Case1.txt");

	int times;

	infile >> times;

	vector < vector<string> > finalans;

	for ( ; times > 0; times--)
	{
		vector <imp1> oneimp;
		vector <imp1> care;
		vector <imp1> one1;
		vector <imp1> twoimp;
		vector <imp1> fourimp;
		vector <imp1> eightimp;
		vector <string> ans;
		bool dontcare[16] = { false };
		bool one2[16] = { false };

		int countone = 0;
		for (int i = 0; i < 16; i++)
		{
			imp1 temp;
			int num;

			infile >> num;

			temp.code = graycode[i];
			temp.term.push_back(term[i]);

			if (num == 1)
			{
				oneimp.push_back(temp);
				one1.push_back(temp);
				countone++;
			}
			else if (num == 2)
			{
				oneimp.push_back(temp);
				care.push_back(temp);
				countone++;
			}
		}
		
		if (countone == 16)
		{
			string tempone1 = "2222";
			vector <string> tempone;
			tempone.push_back(tempone1);
			finalans.push_back(tempone);
			continue;
		}

		for (int i = 0; i < care.size(); i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (care[i].code == binary[j])
				{
					dontcare[j] = true;
				}
			}
		}

		for (int i = 0; i < one1.size(); i++)
		{
			for (int j = 0; j < 16; j++)
			{
				if (one1[i].code == binary[j])
				{
					one2[j] = true;
				}
			}
		}

		sort(oneimp.begin(), oneimp.end(), sort1);

		for (int i = 0; i < oneimp.size(); i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (i == j)
				{
					continue;
				}

				if (bits(oneimp[i].code, oneimp[j].code) == 1)
				{
					imp1 temp;
					temp.term.push_back(oneimp[i].term[0]);
					temp.term.push_back(oneimp[j].term[0]);
					temp.code = newcode(oneimp[i].code, oneimp[j].code);
					twoimp.push_back(temp);
				}
			}
		}

		for (int i = 0; i < twoimp.size(); i++)
		{
			sort(twoimp[i].term.begin(), twoimp[i].term.end(), sort);
		}
		sort(twoimp.begin(), twoimp.end(), sort2);

		int count[16] = { 0 };
		for (int i = 0; i < twoimp.size(); i++)
		{
			count[twoimp[i].term[0]]++;
			count[twoimp[i].term[1]]++;
		}

		bool twoimp1[16] = { false };

		for (int j = 0; j < 16; j++)
		{
			if (count[j] == 1)
			{
				for (int i = 0; i < twoimp.size(); i++)
				{
					if (twoimp[i].term[0] == j)
					{
						twoimp[i].min = true;
						twoimp1[twoimp[i].term[0]] = true;
						twoimp1[twoimp[i].term[1]] = true;
						break;
					}
					else if (twoimp[i].term[1] == j)
					{
						twoimp[i].min = true;
						twoimp1[twoimp[i].term[0]] = true;
						twoimp1[twoimp[i].term[1]] = true;
						break;
					}
				}
			}
		}

		for (int i = 0; i < twoimp.size(); i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (bits(twoimp[i].code, twoimp[j].code) == 1)
				{
					imp1 temp;
					temp.term.push_back(twoimp[j].term[0]);
					temp.term.push_back(twoimp[j].term[1]);
					temp.term.push_back(twoimp[i].term[0]);
					temp.term.push_back(twoimp[i].term[1]);
					temp.code = newcode(twoimp[i].code, twoimp[j].code);
					fourimp.push_back(temp);
				}
			}
		}

		for (int i = 0; i < fourimp.size(); i++)
		{
			sort(fourimp[i].term.begin(), fourimp[i].term.end(), sort);
		}
		sort(fourimp.begin(), fourimp.end(), sort3);

		for (int i = 0; i < fourimp.size() - 1; i++)
		{
			if (fourimp.size() == 0)
			{
				break;
			}
			if ((fourimp[i].term[0] == fourimp[i + 1].term[0]) && (fourimp[i].term[1] == fourimp[i + 1].term[1])
				&& (fourimp[i].term[2] == fourimp[i + 1].term[2]) && (fourimp[i].term[3] == fourimp[i + 1].term[3]))
			{
				fourimp.erase(fourimp.begin() + i + 1);
				i--;
			}
		}

		int count1[16] = { 0 };
		for (int i = 0; i < fourimp.size(); i++)
		{
			count1[fourimp[i].term[0]]++;
			count1[fourimp[i].term[1]]++;
			count1[fourimp[i].term[2]]++;
			count1[fourimp[i].term[3]]++;
		}

		bool fourimp1[16] = { false };

		for (int j = 0; j < 16; j++)
		{
			if (count1[j] == 1 && !dontcare[j] && !twoimp1[j])
			{
				for (int i = 0; i < fourimp.size(); i++)
				{
					for (int m = 0; m < 4; m++)
					{
						if (fourimp[i].term[m] == j)
						{
							fourimp[i].min = true;
							fourimp1[fourimp[i].term[0]] = true;
							fourimp1[fourimp[i].term[1]] = true;
							fourimp1[fourimp[i].term[2]] = true;
							fourimp1[fourimp[i].term[3]] = true;
							break;
						}
					}
				}
			}
		}

		for (int i = 0; i < oneimp.size(); i++)
		{
			if (!dontcare[oneimp[i].term[0]] && count[oneimp[i].term[0]] == false)
			{
				ans.push_back(oneimp[i].code);
				one2[oneimp[i].term[0]] = false;
				oneimp.erase(oneimp.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < twoimp.size(); i++)
		{
			if (twoimp[i].min == true)
			{
				ans.push_back(twoimp[i].code);
				one2[twoimp[i].term[0]] = false;
				one2[twoimp[i].term[1]] = false;
				twoimp.erase(twoimp.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < fourimp.size(); i++)
		{
			if (fourimp[i].min == true)
			{
				ans.push_back(fourimp[i].code);
				one2[fourimp[i].term[0]] = false;
				one2[fourimp[i].term[1]] = false;
				one2[fourimp[i].term[2]] = false;
				one2[fourimp[i].term[3]] = false;
				fourimp.erase(fourimp.begin() + i);
				i--;
			}
		}

		for (int i = 0; i < fourimp.size(); i++)
		{
			for (int j = 0; j < i; j++)
			{
				if (i == j)
				{
					continue;
				}

				if (bits(fourimp[i].code, fourimp[j].code) == 1)
				{
					imp1 temp;
					for (int m = 0; m < 4; m++)
					{
						temp.term.push_back(fourimp[j].term[m]);
					}
					for (int m = 0; m < 4; m++)
					{
						temp.term.push_back(fourimp[i].term[m]);
					}
					temp.code = newcode(fourimp[i].code, fourimp[j].code);
					eightimp.push_back(temp);
				}
			}
		}

		for (int i = 0; i < eightimp.size(); i++)
		{
			sort(eightimp[i].term.begin(), eightimp[i].term.end(), sort);
		}

		sort(eightimp.begin(), eightimp.end(), sort4);

		for (int i = 0; i < eightimp.size() - 1; i++)
		{
			if (eightimp.size() == 0)
			{
				break;
			}
			if ((eightimp[i].term[0] == eightimp[i + 1].term[0]) && (eightimp[i].term[1] == eightimp[i + 1].term[1])
				&& (eightimp[i].term[2] == eightimp[i + 1].term[2]) && (eightimp[i].term[3] == eightimp[i + 1].term[3])
				&& (eightimp[i].term[4] == eightimp[i + 1].term[4]) && (eightimp[i].term[5] == eightimp[i + 1].term[5])
				&& (eightimp[i].term[6] == eightimp[i + 1].term[6]) && (eightimp[i].term[7] == eightimp[i + 1].term[7]))
			{
				eightimp.erase(eightimp.begin() + i + 1);
				i--;
			}
		}

		int count2[16] = { 0 };
		for (int i = 0; i < eightimp.size(); i++)
		{
			for (int m = 0; m < 8; m++)
			{
				count2[eightimp[i].term[m]]++;
			}
		}

		for (int j = 0; j < 16; j++)
		{
			if (count2[j] == 1 && !dontcare[j] && !twoimp1[j] && !fourimp1[j])
			{
				for (int i = 0; i < eightimp.size(); i++)
				{
					for (int m = 0; m < 8; m++)
					{
						if (eightimp[i].term[m] == j)
						{
							eightimp[i].min = true;
							break;
						}
					}
				}
			}
		}

		for (int i = 0; i < eightimp.size(); i++)
		{
			if (eightimp[i].min == true)
			{
				ans.push_back(eightimp[i].code);
				for (int m = 0; m < 8; m++)
				{
					one2[eightimp[i].term[m]] = false;
				}
				eightimp.erase(eightimp.begin() + i);
				i--;
			}
		}

		if (keepfind(one2))
		{
			vector<int> match;
			do
			{
				match.clear();
				//т⒎干
				for (int i = 0; i < eightimp.size(); i++)
				{
					int count = 0;
					for (int j = 0; j < 16; j++)
					{
						if (one2[j] == true)
						{
							for (int m = 0; m < 8; m++)
							{
								if (eightimp[i].term[m] == j)
								{
									count++;
								}
							}
						}
					}

					match.push_back(count);
				}

				if (!non(match))
				{
					int pos = 0;
					for (int i = 0; i < match.size() - 1; i++)
					{
						if (match[i] < match[i + 1])
						{
							pos = i + 1;
						}
					}

					ans.push_back(eightimp[pos].code);
					for (int m = 0; m < 8; m++)
					{
						one2[eightimp[pos].term[m]] = false;
					}
					eightimp.erase(eightimp.begin() + pos);
				}
				else
				{
					break;
				}

			} while (keepfind(one2) && !non(match));

			//т4干
			if (keepfind(one2))
			{
				vector<int> match1;
				do
				{
					match1.clear();
					for (int i = 0; i < fourimp.size(); i++)
					{
						int count = 0;
						for (int j = 0; j < 16; j++)
						{
							if (one2[j] == true)
							{
								for (int m = 0; m < 4; m++)
								{
									if (fourimp[i].term[m] == j)
									{
										count++;
									}
								}
							}
						}

						match1.push_back(count);
					}

					if (!non(match1))
					{
						int pos = 0;
						for (int i = 0; i < match1.size() - 1; i++)
						{
							if (match1[i] < match1[i + 1])
							{
								pos = i + 1;
							}
						}

						ans.push_back(fourimp[pos].code);

						one2[fourimp[pos].term[0]] = false;
						one2[fourimp[pos].term[1]] = false;
						one2[fourimp[pos].term[2]] = false;
						one2[fourimp[pos].term[3]] = false;
						fourimp.erase(fourimp.begin() + pos);
					}
					else
					{
						break;
					}

				} while (keepfind(one2) && !non(match1));
			}

			//т2干
			if (keepfind(one2))
			{
				vector<int> match2;
				do
				{
					match2.clear();
					for (int i = 0; i < twoimp.size(); i++)
					{
						int count = 0;
						for (int j = 0; j < 16; j++)
						{
							if (one2[j] == true)
							{
								if (twoimp[i].term[0] == j)
								{
									count++;
								}
								else if (twoimp[i].term[1] == j)
								{
									count++;
								}
							}
						}

						match2.push_back(count);
					}

					if (!non(match2))
					{
						int pos = 0;
						for (int i = 0; i < match2.size() - 1; i++)
						{
							if (match2[i] < match2[i + 1])
							{
								pos = i + 1;
							}
						}

						ans.push_back(twoimp[pos].code);
						one2[twoimp[pos].term[0]] = false;
						one2[twoimp[pos].term[1]] = false;
						twoimp.erase(twoimp.begin() + pos);
					}
					else
					{
						break;
					}

				} while (keepfind(one2) && !non(match2));
			}

			//т1干
			if (keepfind(one2))
			{
				vector<int> match3;
				do
				{
					match3.clear();
					for (int i = 0; i < oneimp.size(); i++)
					{
						int count = 0;
						for (int j = 0; j < 16; j++)
						{
							if (one2[j] == true)
							{
								if (oneimp[i].term[0] == j)
								{
									count++;
								}
							}
						}

						match3.push_back(count);
					}

					if (!non(match3))
					{
						int pos = 0;
						for (int i = 0; i < match3.size() - 1; i++)
						{
							if (match3[i] < match3[i + 1])
							{
								pos = i + 1;
							}
						}

						ans.push_back(oneimp[pos].code);
						one2[oneimp[pos].term[0]] = false;
						oneimp.erase(oneimp.begin() + pos);
					}
					else
					{
						break;
					}

				} while (keepfind(one2) && !non(match3));
			}
		}

		for (int j = 0; j < ans.size(); j++)
		{
			for (int k = 0; k < 4; k++)
			{
				if (ans[j][k] == 45)
				{
					ans[j][k] = '2';
				}
			}
		}
		sort(ans.begin(), ans.end(), sortans);
		finalans.push_back(ans);
	}

	fstream file;
	file.open("text.txt", ios::out);

	for (int i = 0; i < finalans.size(); i++)
	{
		std::cout << "#" << i + 1 << endl;
		file << '#' << i + 1 << endl;

		for (int j = 0; j < finalans[i].size(); j++)
		{
			cout << finalans[i][j] << endl;
			file << finalans[i][j] << endl;
			//file << endl;
		}
	}
}