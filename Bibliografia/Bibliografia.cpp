#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct bibliografia
{
	string n_Etykieta;
	string imie;
	string nazwisko;
	string tytul;
	int id;
	bibliografia *n;
};
void dod_bib(bibliografia *&gl, string n_Etykieta, string imie, string nazwisko, string tytul)
{
	bibliografia *e = new bibliografia();
	e->imie = imie;
	e->nazwisko = nazwisko;
	e->n_Etykieta = n_Etykieta;
	e->tytul = tytul;

	e->n = NULL;
	if (gl)
	{
		if (gl->nazwisko.compare(nazwisko) < 1)
		{
			dod_bib(gl->n, n_Etykieta, imie, nazwisko, tytul);
		}
		else
		{
			e->n = gl;
			gl = e;
		}
	}
	else
	{
		gl = e;
	}
}
void dod_id(bibliografia *gl)
{
	bibliografia *e = gl;
	int id = 0;
	while (e != NULL)
	{
		e->id = id;
		id++;
		e = e->n;
	}
}
void wyp_bib(bibliografia *gl)
{
	bibliografia *e = gl;
	cout << endl << "Bibliografia: " << endl;
	while (e != NULL)
	{
		cout << "[" << e->id << "] " << e->imie << " " << e->nazwisko << ", " << e->tytul << endl;

		e = e->n;
	}
}
void szukaj(string etykieta, bibliografia *gl)
{
	bibliografia *e = gl;
	while (e != NULL)
	{
		if (etykieta == e->n_Etykieta)
		{
			cout << "[" << e->id << "] ";
		}

		e = e->n;
	}
}
void zam_tekst(bibliografia *gl)
{
	string s;
	ifstream tekst;
	tekst.open("tekst.txt");
	if (!tekst.is_open())
	{
		cout << "brak tekstu";
	}
	else
	{
		while (!tekst.eof())
		{
			tekst >> s;
			if (s[0] == char(92))
			{
				s = s.substr(s.find("{") + 1);
				s = s.substr(0, s.length() - 1);
				szukaj(s, gl);
			}
			else
			{
				cout << s << " ";
			}
		}
		tekst.close();
	}
}
int main()
{
	bibliografia *n = NULL;

	string n_etykieta;
	string imie;
	string nazwisko;
	string tytul;

	ifstream wej;
	wej.open("bibliografia.txt");

	if (!wej.is_open())
	{
		cout << "brak pliku";
	}
	else
	{
		while (!wej.eof())
		{

			getline(wej, n_etykieta);
			getline(wej, imie);
			nazwisko = imie.substr(imie.find(" "));
			imie = imie.substr(0, imie.find(" "));
			getline(wej, tytul);

			dod_bib(n, n_etykieta, imie, nazwisko, tytul);

		}
		wej.close();
	}
	dod_id(n);
	zam_tekst(n);

	wyp_bib(n);

	system("pause");
	return 0;
}