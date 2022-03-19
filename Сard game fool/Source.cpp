#include <iostream>
#include <vector>
#include <windows.h>
#include <conio.h>

using namespace std;
string Names[] = { "6\x06", "7\x06", "8\x06", "9\x06" , "10\x06" , "J\x06" , "Q\x06" ,"K\x06" ,"A\x06" ,
"6\x05", "7\x05", "8\x05", "9\x05" , "10\x05" , "J\x05" , "Q\x05" ,"K\x05" ,"A\x05",
"6\x03", "7\x03", "8\x03", "9\x03" , "10\x03" , "J\x03" , "Q\x03" ,"K\x03" ,"A\x03",
"6\x04", "7\x04", "8\x04", "9\x04" , "10\x04" , "J\x04" , "Q\x04" ,"K\x04" ,"A\x04"
};
string Masti[] = { "\x06" , "\x05", "\x04" , "\x03" };
vector <string> koloda(&Names[0], &Names[36]);
void Menu();
class GamePC
{
private:
	vector <string> Ukoloda;
	vector <string> PCkoloda;
	string Kozir;
public:
	void AddKarts(int u)
	{
		//1-all , 2-PC , 3-U
		int tmp;
		switch (u)
		{
		case 1:
		{
			if (koloda.size() > 1)
			{
				if (Ukoloda.size() < 6)
				{
					tmp = rand() % koloda.size();
					Ukoloda.push_back(koloda[tmp]);
					koloda.erase(koloda.begin() + tmp);
				}
				if (PCkoloda.size() < 6)
				{
					tmp = rand() % koloda.size();
					PCkoloda.push_back(koloda[tmp]);
					koloda.erase(koloda.begin() + tmp);
				}

			}
			break;
		}
		case 2:
		{
			if (koloda.size() > 0)
			{
				if (PCkoloda.size() < 6)
				{
					tmp = rand() % koloda.size();
					PCkoloda.push_back(koloda[tmp]);
					koloda.erase(koloda.begin() + tmp);
				}
			}
			break;
		}
		case 3:
		{
			if (koloda.size() > 0)
			{
				if (Ukoloda.size() < 6)
				{
					tmp = rand() % koloda.size();
					Ukoloda.push_back(koloda[tmp]);
					koloda.erase(koloda.begin() + tmp);
				}
			}
			break;
		}
		}

	}
	void Start()
	{
		if (koloda.size() > 0)
		{
			for (int j = 0; j < 6; j++)
			{
				AddKarts(3);
			}
			for (int j = 0; j < 6; j++)
			{
				AddKarts(2);
			}
			int tmp = rand() % 4;
			Kozir.push_back(*Masti[tmp].c_str());

		}

	}
	void UHod()
	{
	Q:
		int num;
		cout << endl;
		cout << "Enter your move:" << endl;
		cin >> num;
		string umast;
		vector <int > masti;
		string u;
		num--;
		if (num <= Ukoloda.size() && num >= 0)
		{
			u = Ukoloda[num];
			if (u.size() == 3)
				u.erase(0, 2);
			else if (u.size() == 2)
				u.erase(u.begin());
			PoiskMastiPC(u, masti);
			int num2 = 0;
			int poz = -1;
			int num1 = 0;
			//num2 - pc num1 u
			int gh = 0;
			NumberPC(masti, num2, poz, u, num, gh);
			if (poz != -1)
			{
				u = Ukoloda[num];
				if (u.size() == 3)
					u.erase(2, 4);
				else if (u.size() == 2)
					u.erase(1);
				NumberU(u, num1);
				bool t = true;
				//try ěĺíüřĺ false bolshe
				gh = masti.size();
				for (int i = 0; i < gh; i++)
				{
					if (num2 < num1)
					{
						masti.erase(masti.begin());
						NumberPC(masti, num2, poz, u, num, gh);
					}
					else
					{

						ShowTable(poz, num);
						PCkoloda.erase(PCkoloda.begin() + poz);
						Ukoloda.erase(Ukoloda.begin() + num);
						AddKarts(3);
						AddKarts(2);
						break;
					}


				}
			}

		}
		else
		{
			cout << "No such card" << endl;
			goto Q;
		}


	}

	void NumberU(string u, int& num1)
	{
		if (u == "6")
			num1 = 1;
		else if (u == "7")
			num1 = 2;
		else if (u == "8")
			num1 = 3;

		else if (u == "9")
			num1 = 4;

		else if (u == "10")
			num1 = 5;

		else if (u == "J")
			num1 = 6;

		else if (u == "Q")
			num1 = 7;

		else if (u == "K")
			num1 = 8;

		else if (u == "A")
			num1 = 9;
	}
	void NumberPC(vector <int>& D, int& f, int& poz, string u, int num, int& gh)
	{
		string tmp;
		u = Ukoloda[num];
		if (u.size() == 3)
			u.erase(0, 2);
		else if (u.size() == 2)
			u.erase(u.begin());
		if (D.size() == 0 && u != Kozir)
		{
			PoiskMastiPC(Kozir, D);
			if (D.size() > 0)
			{
				gh++;
			}

		}
		if (D.size() > 0)
		{
			for (int i = 0; i < D.size(); i++)
			{
				tmp = PCkoloda[D[i]];
				for (int j = 0; j < PCkoloda.size(); j++)
				{
					if (tmp == PCkoloda[j])
					{
						poz = j;
						break;
					}
				}
				if (tmp.size() == 2)
					tmp.erase(1);
				else if (tmp.size() == 3)
					tmp.erase(2, 4);
				if (tmp == "6")
					f = 1;
				else if (tmp == "7")
					f = 2;
				else if (tmp == "8")
					f = 3;

				else if (tmp == "9")
					f = 4;

				else if (tmp == "10")
					f = 5;

				else if (tmp == "J")
					f = 6;

				else if (tmp == "Q")
					f = 7;

				else if (tmp == "K")
					f = 8;

				else if (tmp == "A")
					f = 9;
				/*	else
						D.clear();*/

				break;
			}

		}
		if (D.size() == 0 /*&& u == Kozir*/)
		{
			PCkoloda.push_back(Ukoloda[num]);
			ShowTable(-1, num);
			Ukoloda.erase(Ukoloda.begin() + num);
			AddKarts(3);
			if (PCkoloda.size() > 0)
			{
				UHod();
			}
		}


		//ňóň ĺëńĺ ĺńëč â őîä ďîřëč ęîçűđ˙
	}
	void  PoiskMastiPC(string a, vector <int>& D)
	{
		string pcmast;
		for (int i = 0; i < PCkoloda.size(); i++)
		{
			pcmast = PCkoloda[i];
			if (pcmast.size() == 2)
				pcmast.erase(pcmast.begin());
			if (pcmast.size() == 3)
				pcmast.erase(0, 2);
			if (pcmast == a)
			{
				D.push_back(i);
			}
		}

	}
	void ShowTable()
	{
		system("CLS");
		for (int i = 0; i < PCkoloda.size(); i++)
		{
			cout << "**" << '\t';
		}
		cout << endl;
		//<< "**" << '\t' << "**" << '\t' << "**" << '\t' << "**" << '\t' << "**" << endl;
		cout << "----------------------------------------------------" << endl;
		cout << endl; cout << endl; cout << endl; cout << endl; cout << endl;
		cout << "----------------------------------------------------" << endl;
		for (int j = 0; j < Ukoloda.size(); j++)
		{
			cout << Ukoloda[j] << '\t';
		}
		cout << endl << endl << endl << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t';
		cout << "Deck size:" << koloda.size() << endl;
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t';
		cout << "Trump:" << Kozir << endl;
		//cout << "Nagmite lybyu klavihy" << endl;
		_getch();
	}

	void ShowTable(int i, int num)
	{
		system("CLS");
		// y = 0 u hod
		// y= 1 hod pc
		for (int i = 0; i < PCkoloda.size() - 1; i++)
		{
			cout << "**" << '\t';
		}
		cout << endl;
		//<< "**" << '\t' << "**" << '\t' << "**" << '\t' << "**" << '\t' << "**" << endl;
		cout << "----------------------------------------------------" << endl;
		cout << endl; cout << endl;

		if (i != -1)
		{
			cout << '\t' << '\t' << '\t' << PCkoloda[i];
		}
		cout << '\t' << '\t' << Ukoloda[num];
		cout << endl; cout << endl;
		cout << "----------------------------------------------------" << endl;
		for (int j = 0; j < Ukoloda.size(); j++)
		{
			if (j != num)
				cout << Ukoloda[j] << '\t';
		}
		cout << endl << endl << endl << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t';
		cout << "Deck size:" << koloda.size() << endl;
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t';
		cout << "Trump:" << Kozir << endl;
		cout << "Press any key" << endl;

		_getch();
	}
	void ShowTableHodPC(int poz, int& tmp)
	{
		system("CLS");
		// y = 0 u hod
		// y= 1 hod pc
		for (int i = 0; i < PCkoloda.size() - 1; i++)
		{
			cout << "**" << '\t';
		}
		cout << endl;
		//<< "**" << '\t' << "**" << '\t' << "**" << '\t' << "**" << '\t' << "**" << endl;
		cout << "----------------------------------------------------" << endl;
		cout << endl; cout << endl;

		cout << '\t' << '\t' << '\t' << PCkoloda[poz];

		cout << endl; cout << endl;
		cout << "----------------------------------------------------" << endl;
		for (int j = 0; j < Ukoloda.size(); j++)
		{
			cout << Ukoloda[j] << '\t';
		}
		cout << endl << endl << endl << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t';
		cout << "Deck size:" << koloda.size() << endl;
		cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t' << '\t';
		cout << "Trump:" << Kozir << endl;
		cout << "Enter your move (0-pass):";
		cin >> tmp;
	}
	string Mast(string u)
	{
		if (u.size() == 3)
			u.erase(0, 2);
		else if (u.size() == 2)
			u.erase(0, 1);
		return u;

	}
	void PChod()
	{
		vector <int> BezKozirov;
		for (int i = 0; i < 4; i++)
		{
			if (Masti[i] != Kozir)
			{
				PoiskMastiPC(Masti[i], BezKozirov);
			}
		}
		if (BezKozirov.size() == 0)
		{
			PoiskMastiPC(Kozir, BezKozirov);
		}
		int i = rand() % BezKozirov.size();
		int poz = BezKozirov[i];
		int tmp = 0;
		ShowTableHodPC(poz, tmp);
		if (tmp != 0 && tmp <= Ukoloda.size())
		{
			string u;
			tmp--;
			int num1 = 0;
			int num2 = 0;
			//num1 u
			//num2 pc
			u = Ukoloda[tmp];
			if (Mast(Ukoloda[tmp]) != Mast(PCkoloda[poz]))
			{
				if (Mast(Ukoloda[tmp]) != Kozir)
				{
					ShowTable(poz, tmp);
					Ukoloda.push_back(PCkoloda[poz]);
					PCkoloda.erase(PCkoloda.begin() + poz);
					AddKarts(2);
					if (Ukoloda.size() > 0)
					{
						PChod();
					}
				}
				else
				{

					ShowTable(poz, tmp);
					PCkoloda.erase(PCkoloda.begin() + poz);
					Ukoloda.erase(Ukoloda.begin() + tmp);
					AddKarts(1);
				}
			}
			else
			{

				if (u.size() == 3)
					u.erase(2, 4);
				else if (u.size() == 2)
					u.erase(1);

				NumberU(u, num1);
				u = PCkoloda[poz];
				if (u.size() == 3)
					u.erase(2, 4);
				else if (u.size() == 2)
					u.erase(1);
				NumberU(u, num2);
				if (num1 > num2)
				{
					ShowTable(poz, tmp);
					PCkoloda.erase(PCkoloda.begin() + poz);
					Ukoloda.erase(Ukoloda.begin() + tmp);
					AddKarts(1);
				}
				else
				{
					Ukoloda.push_back(PCkoloda[poz]);
					PCkoloda.erase(PCkoloda.begin() + poz);
					AddKarts(2);
					ShowTable();
					if (Ukoloda.size() > 0)
					{
						PChod();
					}
				}
			}

		}
		else
		{
			Ukoloda.push_back(PCkoloda[poz]);
			PCkoloda.erase(PCkoloda.begin() + poz);
			AddKarts(2);
			ShowTable();
			if (Ukoloda.size() > 0 && PCkoloda.size() > 0)
			{
				PChod();
			}
		}

	}
	int GetSizeKoloda()
	{
		return koloda.size();
	}
	int GetSizePCkoloda()
	{
		return PCkoloda.size();
	}
	int GetSizeUkoloda()
	{
		return Ukoloda.size();
	}
};

int main()
{

	setlocale(LC_ALL, "Russian");
	srand(time(NULL));
	Menu();
	//03 черва 04 бубна 05 хреста  06 пика
	// 1-49 2-50 3-51 4-52 5-53 6-54
	system("pause");
}
void Menu()
{
	cout << endl << endl << endl << endl << endl << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t';
	cout << "HELLO @everyone" << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t';
	cout << "1.New game" << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t';
	cout << "2.Exit" << endl;
	cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t';
	int tmp = _getch();
	if (tmp == 49)
	{
		GamePC C;
		C.Start();
		C.ShowTable();
		while (true)
		{
			if (C.GetSizeUkoloda() != 0 && C.GetSizePCkoloda() != 0)
			{
				cout << "Your move" << endl;
				C.UHod();
				C.ShowTable();
			}
			else
				break;
			if (C.GetSizeUkoloda() != 0 && C.GetSizePCkoloda() != 0)
			{
				cout << "PC move" << endl;
				C.PChod();
				C.ShowTable();
			}
			else
				break;
		}
		if (C.GetSizeUkoloda() == 0)
		{
			system("CLS");
			cout << endl << endl << endl << endl << endl << endl;
			cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t';
			cout << "You win !!!" << endl;
			cout << endl << endl << endl << endl << endl << endl;

		}
		if (C.GetSizePCkoloda() == 0)
		{
			system("CLS");
			cout << endl << endl << endl << endl << endl << endl;
			cout << '\t' << '\t' << '\t' << '\t' << '\t' << '\t';
			cout << "PC win ..." << endl;
			cout << endl << endl << endl << endl << endl << endl;

		}
	}
	if (tmp == 50)
	{
		system("exit");
	}
}
