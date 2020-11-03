#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

//宏定义
#define MAX 30


//定义学生的结构体
typedef struct
{
    int Num; //学号
    int score[6]; //分数
    char name[24];//姓名
    int rank;//排名
    int sum;//总分
    double ave;//平均分

} student;


//函数原型
//菜单函数
void Show_Menu();
//初始化函数
void Begin_Oper();
//排序函数
void My_Sort(bool (*Type)(int));
//菜单功能函数
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
//输出名词表
void Show_Rank();
//交换函数
void My_Swap(student *s1,student *s2);
//设置排名函数
void Set_Rank();
//输出每个学生的总分和平均分
void Printf_SumAve();

//全局变量
student Stu[MAX];//学生数组
int Current_Nums=0;//目前的学生数量
int Sub_Num=0;//科目数量

int main()
{
    //Begin_Oper();//初始化
    while(1)
    {
        int choice=-1; //用户选择的选项
        Show_Menu();
        scanf("%d",&choice);
        //输入正确,执行选项
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
            //输入有误，重新输入
            puts("Wrong choice! Please choose again!");
            system("pause");
            system("cls");
            break;
        }
    }
    return EXIT_SUCCESS;
}
//函数的实现
//初始化函数
/*
void Begin_Oper()
{
    //从文本导入数据
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
//菜单函数
void Show_Menu()
{
    puts("1．Input record");
    puts("2. Calculate total and average score of every course");
    puts("3. Calculate total and average score of every student");
    puts("4. Sort in descending order by total score of every student");
    puts("5. Sort in ascending order by total score of every student");
    puts("6. Sort in ascending order by number");
    puts("7. Sort in dictionary order by name");
    puts("8．Search by number");
    puts("9. Search by name");
    puts("10.Statistic analysis for every course");
    puts("11．List record");
    puts("0．Exit");
    puts("Please enter your choice:");
}
//结束函数
void Exit()
{
    puts("Thanks you for your using!");
    system("pause");
    exit(0);
}
//输入函数
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
        //如果程序第一次录入学生信息，则要求用户确定科目数量
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
        //将其传入文件
        //fwrite(&Stu[Current_Nums],sizeof(Stu[Current_Nums]),1,Write);
        Current_Nums++;
    }
    printf("Your have add %d students successfully!\n",Add_Num);
    Set_Rank();
    system("pause");
    system("cls");
}
//计算总分和平均分
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
//交换函数
void My_Swap(student *s1,student *s2)
{
    student temp=*s1;
    *s1=*s2;
    *s2=temp;
}
//根据分数降序排列
bool Sort_Score_Fall(int i)
{
    if(Stu[i].sum<Stu[i+1].sum)
        return true;
    else
        return false;
}
//根据分数升序排列
bool Sort_Score_Rise(int i)
{
    if(Stu[i].rank<Stu[i+1].rank)
        return true;
    else
        return false;
}
//按照学号排列
bool Sort_Num(int i)
{
    if(Stu[i].Num>Stu[i+1].Num)
        return true;
    else
        return false;
}
//按照姓名排列
bool Sort_Name(int i)
{
    if(Stu[i].name[0]>Stu[i+1].name[0])
        return true;
    else
        return false;
}
//根据学号进行查找
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
//按照姓名查找
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
//数据分析
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
    //输出数据
    printf("Subject %d:\n",j+1);
    printf("优秀的学生有：%d 占%d%%\n",Score_Sort[0],Score_Sort[0]*100/Current_Nums);
    printf("良好的学生有：%d 占%d%%\n",Score_Sort[1],Score_Sort[1]*100/Current_Nums);
    printf("中等的学生有：%d 占%d%%\n",Score_Sort[2],Score_Sort[2]*100/Current_Nums);
    printf("及格的学生有：%d 占%d%%\n",Score_Sort[3],Score_Sort[3]*100/Current_Nums);
    printf("不及格的学生有：%d 占%d%%\n",Score_Sort[4],Score_Sort[4]*100/Current_Nums);
    }


    system("pause");
    system("cls");

}
//按照输入顺序排序
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
//设置排名函数
void Set_Rank()
{
    int i;
    //先降序排列
    My_Sort(Sort_Score_Fall);
    for(i=0; i<Current_Nums; i++)
    {
        Stu[i].rank=i+1;
    }
}
//排序函数
void My_Sort(bool (*Type)(int))
{
    int i,j;
    //最多进行Current_Num-1轮比较
    Calc_Stu();
    for(i=0; i<Current_Nums-1; i++)
    {
        bool isSorted=true;
        //每一轮比较前Current_Num-1-i个，即已经排序好的最后一个i不用比较
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
