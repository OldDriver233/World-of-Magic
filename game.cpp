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
string weapon[5]={"None","Sword","Shuriken","Magic Wand","Bomb"};
int addoff[5]={0,2,3,5,8};
string armor[5]={"None","Wooden Armor","Cloth Armor","Iron Armor","Shield"};
int adddef[5]={0,1,2,3,5};
//int dropw[5]={0,2,6,10,14};
//int dropa[5]={0,4,8,12,16};
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
        if(remainMon==0)
        {
            system("clear");
            break;
        }
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
        if(res<=10)
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
    int lev,result,exp=0,old[6],prefw,prefa;
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
       fscanf(fp,"%d%d%d%d%d%d%d",&play.off,&play.def,&play.hp,&lev,&exp,&prefw,&prefa);
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
        old[1]=exp;
        exp+=10*(4-result);
        old[2]=play.off;
        old[3]=play.def;
        old[4]=play.hp;
        play.off=15+5*exp/30;
        play.def=3+2*exp/30;
        play.hp=40+10*exp/30;
        play.maxhp=play.hp;
        cout<<"Experience: "<<old[1]<<" -> "<<exp<<endl;
        cout<<"Attack: "<<old[2]<<" -> "<<play.off<<endl;
        cout<<"Defence: "<<old[3]<<" -> "<<play.def<<endl;
        cout<<"HP: "<<old[4]<<" -> "<<play.hp<<endl;
        if((lev-1)%4==0 && lev!=1 && lev<=17)
        {
            cout<<"You've found the ";
            prefa=(lev-1)/4;
            cout<<armor[prefa];
            cout<<"! Defence increase to ";
            play.def+=adddef[prefa];
            cout<<play.def<<endl;
        }
        else if((lev-1)%2==0 && lev<=15)
        {
            cout<<"You've found the ";
            prefw=(lev+1)/4;
            cout<<weapon[prefw];
            cout<<"! Attack increase to ";
            play.off+=addoff[prefw];
            cout<<play.off<<endl;
        }
        cout<<"Do you want to continue?(y/n)?";
        inp='p';
        while(inp!='y'&&inp!='n')
        {
            inp=getchar();
            //cout<<1;
        }
        if(inp=='n')break;
    }
    fp=fopen(play.name.c_str(),"w");
    cout<<"Writing File..."<<endl;
    fprintf(fp,"%d %d %d %d %d %d %d",play.off,play.def,play.hp,lev,exp,prefw,prefa);
    cout<<"bye.";
    fclose(fp);
    return 0;
}
