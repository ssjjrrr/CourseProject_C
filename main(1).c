#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//�궨��
#define MAX 30


//����ѧ���Ľṹ��
typedef struct
{
    int Num; //ѧ��
    int score[6]; //����
    char name[24];//����
    int rank;//����
    int sum;//�ܷ�
    double ave;//ƽ����

} student;


//����ԭ��
//�˵�����
void Show_Menu();
//��ʼ������
void Begin_Oper();
//������
void My_Sort(bool (*Type)(int));
//�˵����ܺ���
void Exit();
void Input_Record();
void Calc_Record();
void Calc_Stu();
bool Sort_Score_Rise(int i);
bool Sort_Score_Fall(int i);
bool Sort_Num(int i);
bool Sort_Name(int i);
void Search();
void Search_Name();
void Static_Analysis();
void List_Record();
//������ʱ�
void Show_Rank();
//��������
void My_Swap(student *s1,student *s2);
//������������
void Set_Rank();
//���ÿ��ѧ�����ֺܷ�ƽ����
void Printf_SumAve();

//ȫ�ֱ���
student Stu[MAX];//ѧ������
int Current_Nums=0;//Ŀǰ��ѧ������
int Sub_Num=0;//��Ŀ����

int main()
{
    //Begin_Oper();//��ʼ��
    while(1)
    {
        int choice=-1; //�û�ѡ���ѡ��
        Show_Menu();
        scanf("%d",&choice);
        //������ȷ,ִ��ѡ��
        switch(choice)
        {
        case 0:
            Exit();
            break;
        case 1:
            Input_Record();
            break;
        case 2:
            Calc_Record();
            break;
        case 3:
            Calc_Stu();
            Printf_SumAve();
            break;
        case 4:
            My_Sort(Sort_Score_Fall);
            Show_Rank();
            break;
        case 5:
            My_Sort(Sort_Score_Rise);
            Show_Rank();
            break;
        case 6:
            My_Sort(Sort_Num);
            Show_Rank();
            break;
        case 7:
            My_Sort(Sort_Name);
            Show_Rank();
            break;
        case 8:
            Search();
            break;
        case 9:
            Search_Name();
            break;
        case 10:
            Static_Analysis();
            break;
        case 11:
            List_Record();
            break;
        default:
            //����������������
            puts("Wrong choice! Please choose again!");
            system("pause");
            system("cls");
            break;
        }
    }
    return EXIT_SUCCESS;
}
//������ʵ��
//��ʼ������
/*
void Begin_Oper()
{
    //���ı���������
    FILE * Read;
    int i=0;
    if((Read=fopen("Students.txt","r"))!=NULL)
    {
        while(!feof(Read))
    {
        fread(&Stu[i],sizeof(Stu[i]),1,Read);
        i++;
    }
       Current_Nums+=i-1;
    }

    return;
}
*/
//�˵�����
void Show_Menu()
{
    puts("1��Input record");
    puts("2. Calculate total and average score of every course");
    puts("3. Calculate total and average score of every student");
    puts("4. Sort in descending order by total score of every student");
    puts("5. Sort in ascending order by total score of every student");
    puts("6. Sort in ascending order by number");
    puts("7. Sort in dictionary order by name");
    puts("8��Search by number");
    puts("9. Search by name");
    puts("10.Statistic analysis for every course");
    puts("11��List record");
    puts("0��Exit");
    puts("Please enter your choice:");
}
//��������
void Exit()
{
    puts("Thanks you for your using!");
    system("pause");
    exit(0);
}
//���뺯��
void Input_Record()
{
    int Add_Num,i,j;
    /*
    FILE *Write;
    if((Write=fopen("Students.txt","a"))==NULL)
    {
        puts("Error! Can't open the file successfully!");
        return;
    }
    */
    if(Sub_Num==0)
    {
        printf("How many subjects you want to add?  ");
        scanf("%d",&Sub_Num);
        //��������һ��¼��ѧ����Ϣ����Ҫ���û�ȷ����Ŀ����
    }
    printf("How many student you want to add?  ");
    scanf("%d",&Add_Num);
    if(Add_Num+Current_Nums>MAX||Sub_Num>6)
    {
        puts("Can not input so many student/subjects!\n");
        system("pause");
        system("cls");

        return;
    }
    for(i=1; i<=Add_Num; i++)
    {
        printf("Please input No.%d Student's Numbers and scores!(Numbers Name)\n",i);
        scanf("%d %s",&Stu[Current_Nums].Num,Stu[Current_Nums].name);
        for(j=0; j<Sub_Num; j++)
        {
            printf("Subject %d : ",j+1);
            scanf("%d",&Stu[Current_Nums].score[j]);
        }
        //���䴫���ļ�
        //fwrite(&Stu[Current_Nums],sizeof(Stu[Current_Nums]),1,Write);
        Current_Nums++;
    }
    printf("Your have add %d students successfully!\n",Add_Num);
    Set_Rank();
    system("pause");
    system("cls");
}
//�����ֺܷ�ƽ����
void Calc_Record()
{
    int sum[6]={0},i,j;
    double ave[6]={0};
    for(i=0;i<Sub_Num;i++)
    {
        for(j=0;j<Current_Nums;j++)
        {
            sum[i]+=Stu[j].score[i];
        }
        ave[i]=((double)sum[i])/((double)Current_Nums);
        printf("Subject %d\n",i+1);
        printf("Sum : %d\t Average : %.2f\n",sum[i],ave[i]);
    }

    system("pause");
    system("cls");
}
//��������
void My_Swap(student *s1,student *s2)
{
    student temp=*s1;
    *s1=*s2;
    *s2=temp;
}
//���ݷ�����������
bool Sort_Score_Fall(int i)
{
    if(Stu[i].sum<Stu[i+1].sum)
        return true;
    else
        return false;
}
//���ݷ�����������
bool Sort_Score_Rise(int i)
{
    if(Stu[i].rank<Stu[i+1].rank)
        return true;
    else
        return false;
}
//����ѧ������
bool Sort_Num(int i)
{
    if(Stu[i].Num>Stu[i+1].Num)
        return true;
    else
        return false;
}
//������������
bool Sort_Name(int i)
{
    if(Stu[i].name[0]>Stu[i+1].name[0])
        return true;
    else
        return false;
}
//����ѧ�Ž��в���
void Search()
{
    int Find_Nums,i,j;
    bool isFind=false;
    puts("Please input the Student's Numbers:");
    if(scanf("%d",&Find_Nums)==1)
    {
        for(i=0; i<Current_Nums; i++)
        {
            if(Stu[i].Num==Find_Nums)
            {
                Set_Rank();
                printf("Numbers: %d\tName: %s \tRank: %d\n",Stu[i].Num,Stu[i].name,Stu[i].rank);
                for(j=0;j<Sub_Num;j++)
                {
                    printf("Subject %d : %d\n",j+1,Stu[i].score[j]);
                }
                puts("");
                isFind=true;
                break;
            }
        }
        if(isFind==false)
        {
            puts("student not found!");
        }
    }
    else
    {
        puts("You have not input the right Numbers!");
    }
    system("pause");
    system("cls");

}
//������������
void Search_Name()
{
    char Find_Name[24];
    int i,j;
    bool isFind=false;
    puts("Please input the Student's Name:");
    scanf("%s",Find_Name);
    for(i=0; i<Current_Nums; i++)
    {
        if(strcmp(Stu[i].name,Find_Name)==0)
        {
            Set_Rank();
            printf("Numbers: %d\tName: %s \tRank: %d\n",Stu[i].Num,Stu[i].name,Stu[i].rank);
                for(j=0;j<Sub_Num;j++)
                {
                    printf("Subject %d : %d\n",j+1,Stu[i].score[j]);
                }
                puts("");
            isFind=true;
            break;
        }
    }
    if(isFind==false)
    {
        puts("student not found!");
    }

    system("pause");
    system("cls");

}
//���ݷ���
void Static_Analysis()
{
    int i,j;
    int Score_Sort[5]= {0};
    for(j=0;j<Sub_Num;j++)
    {
         for(i=0; i<Current_Nums; i++)
    {
        if(Stu[i].score[j]>=90&&Stu[i].score[j]<=100)
            Score_Sort[0]++;
        else if(Stu[i].score[j]>=80&&Stu[i].score[j]<90)
            Score_Sort[1]++;
        else if(Stu[i].score[j]>=70&&Stu[i].score[j]<80)
            Score_Sort[2]++;
        else if(Stu[i].score[j]>=60&&Stu[i].score[j]<70)
            Score_Sort[3]++;
        else if(Stu[i].score[j]>=0&&Stu[i].score[j]<60)
            Score_Sort[4]++;
    }
    //�������
    printf("Subject %d:\n",j+1);
    printf("�����ѧ���У�%d ռ%d%%\n",Score_Sort[0],Score_Sort[0]*100/Current_Nums);
    printf("���õ�ѧ���У�%d ռ%d%%\n",Score_Sort[1],Score_Sort[1]*100/Current_Nums);
    printf("�еȵ�ѧ���У�%d ռ%d%%\n",Score_Sort[2],Score_Sort[2]*100/Current_Nums);
    printf("�����ѧ���У�%d ռ%d%%\n",Score_Sort[3],Score_Sort[3]*100/Current_Nums);
    printf("�������ѧ���У�%d ռ%d%%\n",Score_Sort[4],Score_Sort[4]*100/Current_Nums);
    }


    system("pause");
    system("cls");

}
//��������˳������
void List_Record()
{
    int i,j;

    for(i=0; i<Current_Nums; i++)
    {
        printf("%d\t\t",Stu[i].Num);
        printf("%s\n",Stu[i].name);
        for(j=0;j<Sub_Num;j++)
        {
            printf("Subject %d : %d\n",j+1,Stu[i].score[j]);
        }
        puts("");
        printf("Sum : %d\n",Stu[i].sum);
        printf("Average : %.2f\n",Stu[i].ave);

    }
    system("pause");
    system("cls");


}
//������������
void Set_Rank()
{
    int i;
    //�Ƚ�������
    My_Sort(Sort_Score_Fall);
    for(i=0; i<Current_Nums; i++)
    {
        Stu[i].rank=i+1;
    }
}
//������
void My_Sort(bool (*Type)(int))
{
    int i,j;
    //������Current_Num-1�ֱȽ�
    Calc_Stu();
    for(i=0; i<Current_Nums-1; i++)
    {
        bool isSorted=true;
        //ÿһ�ֱȽ�ǰCurrent_Num-1-i�������Ѿ�����õ����һ��i���ñȽ�
        for(j=0; j<Current_Nums-1-i; j++)
        {
            if(Type(j))
            {
                isSorted=false;
                My_Swap(&Stu[j],&Stu[j+1]);
            }
        }
        if(isSorted)
            break;
    }
}
void Calc_Stu()
{
    int i,j;
    for(i=0;i<Current_Nums;i++)
    {
        for(j=0;j<Sub_Num;j++)
        {
            Stu[i].sum+=Stu[i].score[j];
        }
        Stu[i].ave=((double)Stu[i].sum)/((double)Sub_Num);
    }
}
void Printf_SumAve()
{
    int i;
    for(i=0;i<Current_Nums;i++)
    {
        printf("Numbers : %d \t Name : %s \t Sum: %d \t Average : %.2f\n",Stu[i].Num,Stu[i].name,Stu[i].sum,Stu[i].ave);
    }
    system("pause");
    system("cls");
}
void Show_Rank()
{

    int i;
    for(i=0;i<Current_Nums;i++)
    {
        printf("Numbers : %d \t Name: %s \t Rank: %d\n",Stu[i].Num,Stu[i].name,Stu[i].rank);
    }
    system("pause");
    system("cls");
}
