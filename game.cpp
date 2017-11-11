#include<iostream>
#include<string>
#include<cstdio>
#include<cstdlib>
using namespace std;
struct player{
    string name;
    int off,def,hp,maxhp;
}play,enemy[5];
string nameof[5]={" ","Small Monster","Medium Monster","Big Monster"};
int game(int lv)
{
    int i,remainMon=3,choice;
    double res;
    for(i=1;i<=3;i++)
    {
        enemy[i].off=3*i*lv*0.75;
        enemy[i].def=1*i*lv*0.75;
        enemy[i].hp=7*i*lv*0.75;
        enemy[i].maxhp=enemy[i].hp;
        enemy[i].name=nameof[i];
    }
    while(remainMon)
    {
        //system("clear");
        if(play.hp<=0)break;
        cout<<"\nNow it's your turn.\n";
        cout<<"HP:";
        res=20*play.hp/play.maxhp;
        for(i=1;i<=20;i++)
        {
            if(i<=(int)res)
            cout<<"/";
            else cout<<"-";
        }
        cout<<play.hp<<"/"<<play.maxhp;
        cout<<endl<<"Attack:"<<play.off;
        cout<<" Defence:"<<play.def;
        cout<<" Press 1 to attack and 2 to heal.";
        cin>>choice;
        if(choice==1)
        {
            enemy[4-remainMon].hp-=play.off-enemy[4-remainMon].def;

        }
        else if(choice==2)
        {
            play.hp+=play.off/2;
            if(play.hp>play.maxhp)play.hp=play.maxhp;
        }
        else cout<<"You lost this chance.\n";
        system("clear");
        if(enemy[4-remainMon].hp<=0)
        {   
            cout<<"You defeated the "<<enemy[4-remainMon].name<<" .\n";
            remainMon--;
        }
        if(remainMon==0)break;
        cout<<enemy[4-remainMon].name<<endl;
        cout<<"HP:";
        //cout<<endl;
        res=20*enemy[4-remainMon].hp/enemy[4-remainMon].maxhp;
        for(i=1;i<=20;i++)
        {
            if(i<=(int)res)
            cout<<"/";
            else cout<<"-";
        }
        cout<<enemy[4-remainMon].hp<<"/"<<enemy[4-remainMon].maxhp;
        cout<<endl<<"Attack:"<<enemy[4-remainMon].off;
        cout<<" Defence:"<<enemy[4-remainMon].def;
        if(res<=5)
        {
            enemy[4-remainMon].hp+=enemy[4-remainMon].off/2;
            if(enemy[4-remainMon].hp>enemy[4-remainMon].maxhp)enemy[4-remainMon].hp=enemy[4-remainMon].maxhp;
        }
        else play.hp-=enemy[4-remainMon].off-play.def;
    }
    return remainMon+1;
}

int main()
{
    FILE *fp;
    int lev,result;
    char inp='u';
    cout<<"                 ***World of Magic***\n";
    cout<<"             ***PRESS ANY KEY TO START***\n";
    getchar();
    cout<<"What is your name?";
    cin>>play.name;
    fp=fopen(play.name.c_str(),"r");
    if(fp!=NULL)
    {
       cout<<"Welcome back, "<<play.name<<".\n";
       fscanf(fp,"%d%d%d%d",&play.off,&play.def,&play.hp,&lev);
       play.maxhp=play.hp;
       fclose(fp);
    }
    else
    {
        cout<<"Character not found.\n";
        play.off=15;
        play.def=3;
        play.hp=40;
        play.maxhp=play.hp;
        lev=1;
    }
    while(1)
    {
        result=game(lev);
        if(result==1)
        {
            cout<<"Victory!";
            lev++;
        }
        else cout<<"Defeated.";
        cout<<"\nDo you want to play again(y/n)?";
        inp='p';
        while(inp!='y'&&inp!='n')
        {
            inp=getchar();
            //cout<<1;
        }
        play.off=15+10*lev;
        play.def=3+2*lev;
        play.hp=40+15*lev;
        play.maxhp=play.hp;
        if(inp=='n')break;
    }
    fp=fopen(play.name.c_str(),"w");
    cout<<"Writing File..."<<endl;
    fprintf(fp,"%d %d %d %d",play.off,play.def,play.hp,lev);
    cout<<"bye.";
    fclose(fp);
    return 0;
}