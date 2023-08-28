//编程有两件事让我讨厌：1.写程序不写注释的人  2.要我写注释的人
//因为这个程序的圈复杂度还是有点点大的，所以我还是决定解释一下
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#include <errno.h>
#include <cstdlib>
#pragma pack(4)//自定义对齐数的大小，为什么有对齐数这个东西？不是纯纯浪费空间吗？ 若是你观察一下就会发现一个指针在32位平台或者在64位平台的大小是不一样的
              //所以对于一个变量来说在Windows，或者在Linux，或者在macOS上的大小是不一样的，不具有跨平台的移植性，那么它读取到一个变量长了还得把尾巴砍掉，增加计算量
             //所以这无非是一个取舍问题，我到底是想让程序运行更快，还是想要节约更多空间，要是节约空间的话你可以把对齐数设置为1

typedef struct _Book
//typedef自定义一种类型--因为我懒得写struct  
{
    char name[20];//0-19
    char author[20];//20-39
    char ISBN[20];//40-59
    char type[15];//60-74
    float pricetag = 0;//76-79
    int publictime = 0;//80-83
 char location[10];//84-93   所以最大对齐数为96
}Book;
//结构体内存对齐
//第一个成员变量与结构体在与结构体偏移量为0的地址处
//其他成员变量对齐某个对齐数的整数倍的地址处
//对齐数=编译器默认的一个对齐数，VS默认是8，都是没有对齐数=成员变量的较小值
//结构体总大小为为最大对齐数（每个成员变量都有一个对齐数）的整数倍
//#pragma pack(num)修改默认对齐数,num是一个数


typedef struct _Node
{
    struct _Book book;//里面放了一个Book类型，若要表示Book里面的变量这可以表示成 Node->book->name
    struct _Node* next;
}Node;
//其实也可以使用数组方式?不过这个数组究竟是多大的？因为数组的大小是需要一个常数来规定的
//或许在一些编译器可以使用变量通过一次scanf函数输入数据后可以规定数组的大小,但只有在C99的标准下才能使用这个方式，其他标准下就不行了

char newfilename[20];

//#include "Book.h"//因为在头文件里面引入了系统头文件，所以这里无需再引入一遍

//这个程序最主要的思想就是链表
//所有数据都是一条链上的，对于每次擦除/增添...都是整条链操作


//关于malloc函数：
//描述：Allocates memory blocks.--开辟内存块
//写法：void *malloc( size_t size );所以可以看出malloc函数的返回值是一个void类型的指针
//头文件：<stdlib.h> and <malloc.h>
//兼容性：ANSI, Win 95, Win NT
//返回值：malloc returns a void pointer to the allocated space, or NULL if there is insufficient memory available. 
        //To return a pointer to a type other than void, use a type cast on the return value. The storage space pointed to by the return value is guaranteed to be suitably aligned for storage of any type of object. 
       //If size is 0, malloc allocates a zero-length item in the heap and returns a valid pointer to that item. Always check the return from malloc, even if the amount of memory requested is small.
//参数：size  （Bytes to allocate）所以这里可以看出开辟出来空间的单位是字节
//参考：
/* MALLOC.C: This program allocates memory with
 * malloc, then frees the memory with free.
 */
//#include <stdlib.h>         /* For _MAX_PATH definition */
//#include <stdio.h>
//#include <malloc.h>
//void main(void)
//{
//	char* string;
//
//	/* Allocate space for a path name */
//	string = malloc(_MAX_PATH);
//	if (string == NULL)       这里可以看出如果说开辟内存失败会指向NULL
//		printf("Insufficient memory available\n");
//	else
//	{
//		printf("Memory space allocated for path name\n");
//		free(string);       释放掉刚成功开辟的内存
//		printf("Memory freed\n");
//	}
//}
//更多malloc函数的用法请参考MSDN，更多malloc函数的知识请参考动态内存分配视频：https://www.bilibili.com/video/BV1q54y1q79w/?p=62&vd_source=65a4f9e91c663948c09d68443a0b6b22

//内存的三大区：栈区，堆区，静态区
//栈区：局部变量，函数的形参
//堆区：进行动态内存分配->就是malloc函数操作的区
//静态区：全局变量，静态变量（static ）


//这儿是函数申明，下面的函数很混乱，我也不知道谁前谁后
void inputdate(Node*);
char menu();
void options(char, Node*);
void ls_date(Node*);
int countnum(Node*);
void findbook(Node*);
void savedate(Node*,char);
void touchfile();
void loaddate(Node*,int);
void deldate(Node*);
void modfify_date(Node*);
void sort_date(Node*);

int main()
{
	Node* head = (Node*)malloc(sizeof(Node));//这一步是在创建头节点，不放任何信息。malloc会动态分配内存，但是为甚么我要强制转换他为Node*类型？malloc返回的是void*,如果我不转换会类型不一样。
	head->next = NULL;//头节点的后的节点指向一个空，这是为了确保下次我每次加进来的节点都是这条数据链的最后一个——尾插法
	//printf("%d\n", sizeof(Book));
	int back = 0;
	loaddate(head,back);
	system("pause");//控制台传入一个暂停
	system("cls");//然后清屏
	char option='0';
	 while (1)//死循环，为的就是让用户必须输入'0'还是'1'，并且一直调用
	{
		option = menu();
		if (option >= '1' && option <= '7')
		{
			options(option, head);
		}
		else if(option=='8')//等于8就终止程序
		{
			printf("已退出，不欢迎下次使用\n");
			break;
		}
		else
		{
			printf("错误参数，请从新输入！！\n");
			continue;
		}
		system("pause");
		system("cls");
	}
	return 0;
}





char menu()
{
    printf("******图书管理系统******\n");
    printf("******1.读取数据*******\n");
    printf("******2.保存数据*******\n");
    printf("******3.录入数据*******\n");
    printf("******4.查找数据*******\n");
    printf("******5.删除数据*******\n");
    printf("******6.修改数据*******\n");
    printf("******7.统计数据*******\n");
    printf("******8.退出登录*******\n");
    printf("警告：在执行2-7（包括2-7）操作之前你需要先执行 1 操作，若没有读取数据的操作会默认写入test.txt文件内！！！\n");
    printf("警告：在执行2-7（包括2-7）操作之前你需要先执行 1 操作，若没有读取数据的操作会默认写入test.txt文件内！！！\n");
    printf("警告：在执行2-7（包括2-7）操作之前你需要先执行 1 操作，若没有读取数据的操作会默认写入test.txt文件内！！！\n");
    printf("在输入时每个元素用空格隔开！！！\n");
    printf("请按对应键选择\n");
    char judge = _getch();//其实可以选择使用sacnf，然后用getchar把回车吸收了，但是我感觉每次都要按回车实在是太蠢了，所以这个函数的优点就是无需使用回车，使用请引头函数conio
    return judge;
}

void options(char option, Node* head)//这个函数十分简单，不做注释
{
    char save = 'y';
    int tmp;
    char temp = '1';
    char unuseful[20];
    int back = 1;
    switch (option)
    {

    case '1':
        loaddate(head,back);
        break;

    case '2'://这儿可以把这些封装为一个函数，但是我懒
        ls_date(head);
        printf("你共录入了%d：本书\n", tmp=countnum(head));
        if (tmp>=1)
        {
            printf("这些新数据你需要保存嘛？保存（y）,不保存（n）\n");
            save = _getch();
            if (save == 'y')
            {
                printf("保存到已有文件（0），创建新文件（1）？？？\n");
                while (true)
                {
                    temp = getch();
                    if (temp == '0')
                    {
                        savedate(head,temp);
                        break;
                    }
                    else if (temp == '1')
                    {
                        touchfile();
                        savedate(head,temp);
                        break;
                    }
                    else
                    {
                        printf("请输入0或1！！！\n");
                        continue;
                    }
                }   
            }
            else
            {
                printf("数据未保存");
            }
        }
        break;
    case '3':
        inputdate(head);
        break;
    case '4':
        findbook(head);
        break;
    case '5':
        deldate(head);
        break;
    case '6':
        modfify_date(head);
        break;
    case '7':
        sort_date(head);
        break;
    default:
        printf("请输入1-8之间\n");
        break;
    }
}
//malloc函数的介绍
void inputdate(Node* head)//这里是插入数据，我需要将插入的节点放到最后
{
    Node* newnode = (Node*)malloc(sizeof(Node));//这是我需要插入进去的节点
    newnode->next = NULL;//我让它的下一个节点指向空
    printf("请依次输入图书信息：书名、作者、ISBN、类型、价格、发行时间、存放位置\n");
    //scanf_s("%s %s %s %s %f %d %s", newnode->book.name, 20, newnode->book.author, 20, newnode->book.ISBN, 20, newnode->book.type, 15, &newnode->book.pricetag, &newnode->book.publictime, newnode->book.location, 10);
    scanf("%s %s %s %s %f %d %s", newnode->book.name,  newnode->book.author,  newnode->book.ISBN, newnode->book.type,  &newnode->book.pricetag, &newnode->book.publictime, newnode->book.location);//数组不需要取地址的操作
    Node* move = head;//你可以理解他是一个工具，它的存在就是找出节点的尾部在哪
    while (move->next != NULL)//只要没到最后一个节点就继续移动
    {
        /*printf("test\n");*/
        move = move->next;//移动中
    }
    move->next = newnode;//当move的下一个节点是空的时候，就把新的节点加进来，当新的节点加进来之后在这个新节点（也就是最后一个节点）的下一个节点还是空，因为在定义新节点的时候就把它的后一个节点赋为空
    //通过这么一通操作后就可以在这条数据链上最后一个节点的下一个节点是空，只要某一个节点的写一个节点是空，那么你就可以确定这个节点就是最后一个节点
    //下面的函数原理都是这个就再做注释了
}

void ls_date(Node* head)
{
    Node* move= head->next;
    while (move != NULL)
    {
        printf("书名：%-20s 作者：%-20s ISBN：%-20s 类型：%-15s 价格：%-3g 发行时间：%-4d 存放位置：%-10s\n",  move->book.name, move->book.author, move->book.ISBN, move->book.type, move->book.pricetag, move->book.publictime, move->book.location);
        move = move->next;
    }
}

int countnum(Node* head)//这是一个计数的函数，让用户知道在他打开的这个文件中记录了多少本书
{
    Node* move = head->next;
    int count = 0;
    while (move!=NULL)
    {
        count += 1;
        move = move->next;
    }
    return count;
}


void findbook(Node* head)
{
    char choose = '0';
    Node* move = head->next;
    char target[20];
    int var,terminate=1;
    printf("你要选择那种查找方式? ISBN（0） 书名（1）\n");
    while (1)
    {
        //scanf_s("%d", &choose);
        //getchar();
        choose = _getch();
        if (choose=='0')
        {
            printf("请输入你需要查询书本的ISBN\n");//这里我设计了两种查询的方法，通过书名和唯一的ISBN
            // scanf_s("%s", target, 20);
            scanf("%s", target);
            getchar();
            var = strcmp(target, move->book.ISBN);//这是在在比较两个字符串的内容，相等strcmp函数就会返回数字0
            if (var==0)
            {
                printf("ISBN为%s的书本信息为：书名：%-20s 作者：%-20s ISBN：%-20s 类型：%-15s 价格：%-3g 发行时间：%-4d 存放位置：%-10s\n", target, move->book.name, move->book.author, move->book.ISBN, move->book.type, move->book.pricetag, move->book.publictime, move->book.location);
                terminate = 0;
                break;
            }
            else
            {
                while (var != 0)
                {
                    var = strcmp(target, move->book.ISBN);
                    if (var == 0)
                    {
                        printf("ISBN为%s的书本信息为：书名：%-20s 作者：%-20s ISBN：%-20s 类型：%-15s 价格：%-3g 发行时间：%-4d 存放位置：%-10s\n", target, move->book.name, move->book.author, move->book.ISBN, move->book.type, move->book.pricetag, move->book.publictime, move->book.location);
                        terminate = 0;
                        break;
                    }
                    else
                    {
                        move = move->next;//如果不相等就继续查找写一本
                        if (move==NULL)//如果遇到空都还没有找到，那就是没有这本书喽
                        {
                            printf("系统没有记录这本书的信息！！");
                            terminate = 0;
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
        }
        else if(choose=='1')
        {
            printf("请输入你需要查询书本的书名\n");
            scanf("%s", target);
            getchar();
            var = strcmp(target, move->book.name);
            if (var==0)
            {
                printf("书名为%s的书本信息为：书名：%-20s 作者：%-20s ISBN：%-20s 类型：%-15s 价格：%-3g 发行时间：%-4d 存放位置：%-10s\n", target, move->book.name, move->book.author, move->book.ISBN, move->book.type, move->book.pricetag, move->book.publictime, move->book.location);
                terminate = 0;
            }
            else
            {
                while (1)
                {
                    var = strcmp(target, move->book.name);
                    if (var==0)
                    {
                        printf("书名为%s的书本信息为：书名：%-20s 作者：%-20s ISBN：%-20s 类型：%-15s 价格：%-3g 发行时间：%-4d 存放位置：%-10s\n",target, move->book.name, move->book.author, move->book.ISBN, move->book.type, move->book.pricetag, move->book.publictime, move->book.location);
                        terminate = 0;
                        break;
                    }
                    else
                    {
                        move = move->next;
                        if (move == NULL)
                        {
                            printf("系统没有记录这本书的信息！！");
                            terminate = 0;
                            break;
                        }
                        else
                        {
                            continue;
                        }
                    }
                }
            }
        }
        else
        {
            printf("请输入1或0！！！\n");
            continue;
        }
        if (terminate == 0)
        {
            break;
        }
        else
        {
            continue;
        }
    }
    
}

void touchfile()//创建文件-在目录里并没有对这个函数的申明，整合在保存选项里面了
{
    printf("输入你需要创建的文件名.后缀名\n");
    scanf("%s", newfilename);
    getchar();
    FILE* file = fopen(newfilename, "w");
    if (file==NULL)
    {
        printf("文件创建失败，失败原因为%s\n", strerror(errno));
        return;
    }
    fclose(file);
}

void savedate(Node* head,char tmp1)//tmp1是判断用户是想写入已有的文件，还是保存到新建文件
{
    FILE* file;
    char filename[20];
    if (tmp1=='0')
    {
        printf("请输入你需要保存的位置 文件名.后缀名\n");
        scanf("%s", filename);
        getchar();
        //关于fopen函数：
        //用法：  FILE *fopen( const char *filename, const char *mode );
        //        FILE* _wfopen(const wchar_t* filename, const wchar_t* mode);
        //返回值：Each of these functions returns a pointer to the open file. A null pointer value indicates an error.  如果失败就会返回一个空指针
        //头文件：<stdio.h>
        file = fopen(filename, "w");//w是覆写，a是追加，和Linux中>,>>是一个意思，除此之外还有r,"w+","a+" 等等
    }
    else if(tmp1=='1')
    {
        file = fopen(newfilename, "w");//这儿使用的是全局变量，这个文件名由上面的touchfile函数修改全局变量，在这儿直接使用
    }
    else
    {
        file = fopen("test.txt", "w");
    }
    Node* move = head->next;
    int tmp=0;
    while (move!=NULL)
    {
        tmp = fwrite(&move->book, sizeof(Book), 1, file);
        //关于fwrite函数
        // 描述：Writes data to a stream. 写入数据到一个流
        // 语法：size_t fwrite( const void *buffer, size_t size, size_t count, FILE *stream ); 简单来说就是，写什么东西（需要的是指针/地址），写多大，写几次（块），写到那里去。fread函数参数和这个一样。
        //头文件：<stdio.h>
        //返回值：fwrite returns the number of full items actually written, which may be less than count if an error occurs. Also, if an error occurs, the file-position indicator cannot be determined.
        if (tmp!=1)
        {
            printf("数据写入失败，失败原因为：%s", strerror(errno));//这儿使用了strerror函数显示为操作失败的原因，可能的原因可能由磁盘扇叶损坏、没有这个文件、没有权限。使用这个函数需要引头文件errno
            return;
        }
        move = move->next;
    }
    fclose(file);
}

void loaddate(Node* head,int back)//这里是从文件读取数据，若是用户没有操作则自动操作test.txt,由形参back来判断      
{
    char filename[20];
    char choose = 'y';
    FILE* file;
    int i = 0;
    if (back==0)
    {
        file = fopen("test.txt", "r");//就怕用户不打开文件，文件也不知道保存到那里去，这样可以防止数据未保存就退出，所以在程序一开始就默认打开test.txt
    }
    else
    {
        printf("请输入学要打开的文件名.后缀名\n");
        scanf("%s", filename);
        getchar();
        file = fopen(filename, "r");//这里是读所以是r
    }
    if (!file)
    {
        printf("文件打开失败，失败原因为：%s\n", strerror(errno));
        if(back==0)
        {
            printf("系统已经自动生成一个文件：test.txt!!\n");
            file=fopen("test.txt","a");
        }
        return ;//因为这儿是个空，所以若是文件打开失败则直接结束这函数
    }
    Node* move = head;
    Node* newnode = (Node*)malloc(sizeof(Book));
    newnode->next = NULL;
    if (back==0)
    {
        choose = 'n';
    }
    else
    {
        printf("你需要查看文件中的数据嘛？ 需要（y）,不需要（n）\n");
        choose = _getch();
    }

    if (choose=='y')
    {
        while (fread(&newnode->book, sizeof(Book), 1, file) == 1)
        {
            move->next = newnode;
            move = move->next;
            printf("书名：%-20s 作者：%-20s ISBN：%-20s 类型：%-15s 价格：%-3g 发行时间：%-4d 存放位置：%-10s\n", move->book.name, move->book.author, move->book.ISBN, move->book.type, move->book.pricetag, move->book.publictime, move->book.location);
            newnode = (Node*)malloc(sizeof(Book));
            newnode->next = NULL;
        }
    }
    else if (choose=='n')
    {
        while (fread(&newnode->book, sizeof(Book), 1, file) == 1)//fread读取不成功会返回0
        {
            move->next = newnode;
            move = move->next;
            newnode = (Node*)malloc(sizeof(Book));
            newnode->next = NULL;
        }
    }
    else
    {
        printf("错误指令，已退出！！");
        return;

    }
    //free(newnode);//因为在循环外先创建了一个newnode,加上循环里面的会多一次，所以通过free函数来释放掉这多创建出来的
    fclose(file);
    if (back==0)
    {
        if (countnum(head) >= 1)
        {
            printf("test.txt数据加载成功\n");//在这儿我只是想提醒用户目前打开的是test.txt默认文件
        }
        else
        {
            printf("test.txt文件中没有数据！\n");
        }
        
    }
    else
    {
        
        /*while (filename[i]!='0')
        {
            printf("%c", filename[i]);
            i++;
        }*/
        if (countnum(head)>=1)
        {
            printf("数据加载成功\n");
        }
        else
        {
            printf("在当前打开的文件中没有数据！\n");
        }
    }
    
}

void deldate(Node* head)
{
    Node* move = head;
    char book_name[20];
    printf("请输入你需要删除的书名！\n");
    scanf("%s", book_name);
    getchar();
    while (move->next!=NULL)
    {
        
        if (strcmp(book_name, move->next->book.name) == 0)
        {
            Node* temp = NULL;//尽量不要让他成为野指针，所谓野指针就是没有赋值的指针。就像一个变量没有赋值那么它就是随机值，如果一个指针没有赋初值那他指向的内存也是随机的
            temp = move->next;//这一步其实就是一个删除的动作，我把它拿走了
            move->next = move->next->next;//从找到需要删除的节点后的每一个个节点都向后移动一位，即就是move=move->next，到最后move的next还是空
            //free(temp);//释放掉需要删除的节点，但这个函数在某些编译器的某些情况会报错
            temp = NULL;//不让它成为野指针
            savedate(head,'2');
            printf("删除成功");
            return;

        }
        move = move->next;
    }

}

void modfify_date(Node* head)
{
    Node* move = head->next;
    char bookname[20]; 
    printf("请输入你需要修改的书名\n");
    scanf("%s", bookname);
    getchar();
    while (move!=NULL)
    {
        
        if (strcmp(bookname,move->book.name)==0)
        {
            printf_s("请依次修改%s的作者、ISBN，类型、价格、发行时间、存放位置\n", bookname);
            scanf("%s %s %s %f %d %s", move->book.author, move->book.ISBN, move->book.type, &move->book.pricetag, &move->book.publictime, move->book.location);//这里没有修改书名，原因是：如果这个书名有误那就找不到这个数据，如果数据无误那就没必要修改
            printf("修改成功,如需保存请记得只主菜单页面进行保存“数据操作”!!!\n");                                                                             //其实也可以通过switch语句修改某个特定数据，不过用户又要多选择一次。当然你也可以做一个模糊匹配，不过这样就更麻烦
            return;
        }
        move = move->next;
    }
    printf("你打开的文件中没有你输入的这本书：%s\n", bookname);
}


void sort_date(Node* head)
{
    Node* external_circulation = head->next;
    Node* internal_circulation = head->next;
    char var = '0';
    printf("你要按照那种方式排序？  按照价格排序（0），按照发行时间排序（1）\n");
    var = _getch();
    Book tmp;
    bool mark = 1;
    while (true)
    {
        if (var == '0')
        {
            for (external_circulation; external_circulation->next != NULL; external_circulation = external_circulation->next)
            {  
                mark = 1;
                for (internal_circulation=head->next; internal_circulation->next != NULL; internal_circulation = internal_circulation->next)
                {
                    if (internal_circulation->book.pricetag<internal_circulation->next->book.pricetag)
                    {
                        tmp = internal_circulation->next->book;
                        internal_circulation->next->book = internal_circulation->book;
                        internal_circulation->book = tmp;
                        mark = 0;
                        
                    }   
                }
                if (mark == 1)
                {
                    break;
                }   
            } 
            break;
        }
        else if(var=='1')
        {  
            for (; external_circulation->next != NULL; external_circulation = external_circulation->next)
            {
                mark = 1;
                for (internal_circulation = head->next; internal_circulation->next != NULL; internal_circulation = internal_circulation->next)
                {  
                    if (internal_circulation->book.publictime<internal_circulation->next->book.publictime)
                    {
                        tmp = internal_circulation->book;
                        internal_circulation->book = internal_circulation->next->book;
                        internal_circulation->next->book = tmp;
                    }
                }
                if (mark==1)
                {
                    break;
                }
            }
            break;
        }
        else
        {
            printf("你输入的参数有误，请从新输入！\n");
            continue;
        }
    }
    printf("此次排序是按照降幂排序！\n");
    ls_date(head);
    printf("\n对此次排序系统不会保存，如需保存请在主菜单操作页面进行“保存数据操作”\n");
}