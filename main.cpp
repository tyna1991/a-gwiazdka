#include <iostream>
#include <vector>
#include <algorithm>
#include <math.h>
#define WIERSZE 20
#define KOLUMNY 20
//0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//5 0 0 0 5 5 5 5 5 0 0 0 0 0 0 0 0 0 0 0
//5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//5 0 0 0 0 0 0 0 0 0 5 5 5 5 5 5 5 5 5 5
//5 0 0 0 0 0 0 0 0 0 0 0 0 0 5 5 5 0 0 0
//5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 5 0 0 0 0 0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
//0 0 0 0 0 0 0 0 0 0 0 0 5 5 5 5 5 5 5 5
//0 0 0 0 0 0 5 5 5 5 5 5 5 0 0 0 5 0 0 0
//0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0 5 0 5 0
//0 0 0 0 5 0 0 0 0 0 0 5 5 5 5 5 5 5 5 5
//0 0 5 0 5 0 0 0 0 0 0 0 0 0 0 0 5 0 5 0
//0 0 5 0 5 0 0 0 0 0 0 0 0 0 0 0 5 0 5 0
//5 5 5 5 5 5 5 5 5 5 0 5 5 5 5 5 5 5 5 5
//0 0 0 0 5 0 0 0 0 0 0 0 0 0 0 0 5 0 5 5
//0 0 0 0 5 0 0 0 0 0 0 0 0 0 0 0 5 5 5 5
//0 0 0 0 5 0 0 0 0 0 0 0 0 0 0 0 0 0 0 0
using namespace std;
class Wezel
{
public:
    int x;  //współrzędna x
    int y;  //współrzędna y
    double f;
    double g;
    double h;
    int czymJestem;
    vector<Wezel*> sasiedzi;
    Wezel* poprzedni=0;
    Wezel(): f(0), g(0), h(0), x(0), y(0) {}
    Wezel(int pozx, int pozy)
    {
        x=pozx;
        y=pozy;
        g=0;
        f=0;
        h=0;
    }
    void dodajSasiadow(Wezel mapa [KOLUMNY][WIERSZE])
    {
        if (x<KOLUMNY-1)
        {
            sasiedzi.push_back(new Wezel(x+1,y));
        }
        if (y>0)
        {
            sasiedzi.push_back(new Wezel(x,y-1));
        }
        if (x>0)
        {
            sasiedzi.push_back(new Wezel (x-1,y));
        }
        if (y<WIERSZE-1)
        {
            sasiedzi.push_back(new Wezel(x,y+1));
        }
    }

    bool operator==( const Wezel *rhs)const
    {
        return (rhs->x == this->x && rhs->y==this->y);
    }
    double wyznaczHeurystyke(Wezel *pozycja, Wezel *cel)
    {
        double h=sqrt( pow((pozycja->x - cel->x),2) + pow((pozycja->y - cel->y),2) );
        return h;
    }
    bool czySaTakieSame(Wezel *sasiad)
    {
        return sasiad->x == this->x && sasiad->y==this->y;
    }
};

int main()
{

    vector<Wezel*> zamknietewezly;
    vector<Wezel*> otwartewezly;
    Wezel *start;   //inicjacja - węzeł początkowy
    Wezel *koniec;  //inicjacja - węzeł końcowy
    vector <Wezel*> przeszkody; //inicjacja przeszkod
    vector<Wezel> trasa;    //droga od początku do końca
    Wezel mapa [KOLUMNY][WIERSZE];
    for (int i=0; i<KOLUMNY; i++)   //inicjacja obiektów
    {
        for(int j=0; j<WIERSZE; j++)
        {
            mapa[i][j]=Wezel(i,j);
        }
    }
    for (int i=0; i<KOLUMNY; i++)   //dodanie sąsiadów
    {
        for(int j=0; j<WIERSZE; j++)
        {
            mapa[i][j].dodajSasiadow(mapa);
        }
    }

    int tablica [20][20]={
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {5,0,0,0,5,5,5,5,5,0,0,0,0,0,0,0,0,0,0,0},
    {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {5,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5,5},
    {5,0,0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,0,0,0},
    {5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5,5,5,5,5},
    {0,0,0,0,0,0,5,5,5,5,5,5,5,0,0,0,5,0,0,0},
    {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,5,0,5,0},
    {0,0,0,0,5,0,0,0,0,0,0,5,5,5,5,5,5,5,5,5},
    {0,0,5,0,5,0,0,0,0,0,0,0,0,0,0,0,5,0,5,0},
    {0,0,5,0,5,0,0,0,0,0,0,0,0,0,0,0,5,0,5,0},
    {5,5,5,5,5,5,5,5,5,5,0,5,5,5,5,5,5,5,5,5},
    {0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,5,0,5,5},
    {0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,5,5,5,5},
    {0,0,0,0,5,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0}
    };
    for (int i=0;i<20;i++)
    {
        for(int j=0;j<20;j++)
        {
            if (tablica[i][j]==5)
            {
                przeszkody.push_back(&mapa[i][j]);
                mapa[i][j].czymJestem=5;
            }
           else{
                mapa[i][j].czymJestem=0;
           }
        }
    }

    start=&mapa[0][0];  //węzeł początkowy
    koniec=&mapa[19][19]; //węzeł końcowy
    otwartewezly.push_back(start);  //dodanie węzła do otwartych węzłów
    while (otwartewezly.size()>0)   //dopóki będą otwarte węzły
    {
        int zmienna=0;
        int *najmniejsze_f=&zmienna;
        for (unsigned int i=0; i<otwartewezly.size(); i++)
        {
            if (otwartewezly[i]->f<otwartewezly[*najmniejsze_f]->f)
            {
                *najmniejsze_f=i;   //szukanie najmniejszego f w węzłach
            }
        }
        //cout<<"najmniejsze_f: "<<*najmniejsze_f<<endl;
        Wezel *obecny;
        obecny=otwartewezly[*najmniejsze_f];
        if ((obecny->x==koniec->x) && (obecny->y==koniec->y))
        {
            cout<<endl;
            cout<<"KONIEC!!!!"<<endl;
            cout<<endl;
            Wezel tmp=*obecny;
            tmp.czymJestem=1;
            trasa.push_back(tmp);
            while (tmp.poprzedni)
            {
                tmp.poprzedni->czymJestem=1;
                trasa.push_back(*tmp.poprzedni);
                tmp=*tmp.poprzedni;
            }
            cout<<"Trasa od punktu punktu poczatkowego do konca:"<<endl;
           for(unsigned int i=0; i<trasa.size(); ++i)
            {
                cout<<"wezel nr: "<<i<<" , x: "<<trasa[i].x<<", y: "<<trasa[i].y<<endl;
            }
            for(int i=0; i<KOLUMNY; i++)
            {
                for(int j=0; j<WIERSZE; j++)
                {
                    cout<<mapa[i][j].czymJestem<<" ";
                }
                cout<<endl;
            }
            return 0;
        }
        otwartewezly.erase(otwartewezly.begin() + *najmniejsze_f);
        zamknietewezly.push_back(obecny);
        cout<<endl;
        cout<<"********************rozpatrywany wezel x i y: ****************"<<obecny->x<<", "<<obecny->y<<endl;
        cout<<endl;
        for (unsigned int i=0; i<obecny->sasiedzi.size(); i++)
        {
            cout<<"rozpatrywany sasiad nr: "<<i<<": "<<obecny->sasiedzi[i]->x<<", "<<obecny->sasiedzi[i]->y<<endl;
            Wezel *sasiad;
            sasiad=obecny->sasiedzi[i]; //przypisywanie sąsiada do wskaźnika
            bool jestWZamknietychWezlach=false;
            bool jestPrzeszkoda=false;
            for(unsigned int i=0; i<zamknietewezly.size(); i++)
            {
                if(zamknietewezly[i]->czySaTakieSame(sasiad))
                {
                    jestWZamknietychWezlach=true;
                }
            }
            for(unsigned int i=0; i<przeszkody.size(); i++)
            {
                if(przeszkody[i]->czySaTakieSame(sasiad))
                {
                    jestPrzeszkoda=true;
                }
            }
            cout<<"jest w zamknietych wezlach?: "<<jestWZamknietychWezlach<<endl;
            if(!jestWZamknietychWezlach && !jestPrzeszkoda)
            //if (!(find(zamknietewezly.begin(),zamknietewezly.end(), *sasiad) != zamknietewezly.end())) //je¿eli nie znaleziono sasiada w zamknietych wezlach
            {
                int tmp_g=obecny->g+1;  //koszt g
                int sasiad_x=sasiad->x; //współrzędna x sąsiada
                int sasiad_y=sasiad->y; //współrzędna y sąsiada
                Wezel *znaleziony;      //inicjacja wskaźnika na węzeł
                znaleziony=&mapa[sasiad_x][sasiad_y];   //przypisanie
                bool jestWOtwartchWezlach=false;
                for(unsigned int i=0; i<otwartewezly.size(); i++)
                {
                if(otwartewezly[i]->czySaTakieSame(sasiad))
                    {
                    jestWOtwartchWezlach=true;
                    }
                }
                //if (!(find(otwartewezly.begin(),otwartewezly.end(),sasiad) != otwartewezly.end())) //je¿eli !! nie znaleziono!! sasiada w otwartych wezlach
                if (!jestWOtwartchWezlach)
                {
                    otwartewezly.push_back(znaleziony);
                    znaleziony->h=0;
                    znaleziony->wyznaczHeurystyke(znaleziony, koniec);
                    znaleziony->g=tmp_g;
                }
                else
                {   cout<<"Jest juz w otwartych"<<endl;
                    if (tmp_g<znaleziony->g)
                    {
                        znaleziony->g=tmp_g;
                    }
                }
                znaleziony->h=znaleziony->wyznaczHeurystyke(znaleziony,koniec);
                znaleziony->f=znaleziony->g+znaleziony->h;
                znaleziony->poprzedni=obecny;
                //cout<<"wartosc f: "<<znaleziony->f<<endl;

            }
        }
    }
    return 0;
}
