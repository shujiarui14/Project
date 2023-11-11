import sun.java2d.pipe.SpanShapeRenderer;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;
//用面向过程解决零钱通问题
public class NormalProgramming {
    public static void main(String[] args) {

        String choose=" ";
        double total=0,balance=0;
        Date date=null;
        SimpleDateFormat std=new SimpleDateFormat("yyyy-MM-dd  HH:mm");
        String detail=null;
        String note="";
        String certaian="n";
        do{
            System.out.println("--------------零钱通系统-------------");
            System.out.println("-------------1、查看流水-------------");
            System.out.println("---------------2、收入---------------");
            System.out.println("---------------3、支出---------------");
            System.out.println("-------------4、退出系统-------------");
            System.out.println("请输入对应操作");
            Scanner myScanner= new Scanner(System.in);
            choose=myScanner.next();

            switch (choose)
            {
                case "1":
                {
                    if (detail==null)
                    {
                        System.out.println("你的账户没有任何交易信息");
                    }
                    else
                    {
                        System.out.println(detail);
                    }

                    break;
                }
                case "2":
                {
                    System.out.print("请输入收入金额：");

                    while(true)
                    {
                        balance=myScanner.nextDouble();
                        if (balance>=100000)
                        {
                            System.out.println("系统警告，操作数额过大，可能涉及洗钱，请联系客服证明资产来源后再存入");
                            System.out.println("本次未收入到你的账户，请输入合法金额后再试一次");
                        }
                        else
                        {
                            date=new Date();
                            total+=balance;
                            detail+="\n"+"收入：+" + balance+"\t"+std.format(date)+"\t余额为："+total;

                            break;
                        }
                    }
                    break;
                }
                case "3":
                {
                    System.out.print("请输入支出金额：");
                    balance=myScanner.nextDouble();
                    while (true)
                    {
                        if (balance<=total)
                        {
                            total-=balance;
                            System.out.print("请输入用在何处：");
                            note=myScanner.next();
                            break;
                        }
                        else
                        {
                            System.out.println("你的账户没有这么多钱！！！");
                            System.out.println("请输入低于你总资产的余额后再试一次");
                            System.out.println("提示，你的余额为" + total);
                            balance=myScanner.nextDouble();
                            continue;
                        }
                    }

                    date=new Date();
                    detail+="\n"+"支出："+note+"\t-"+balance+"\t"+std.format(date)+"\t余额为"+total;
                    break;
                }
                case "4":
                {
                    System.out.println("确定要退出系统吗？y/n");
                    certaian=myScanner.next();
                    while (true)
                    {
                        if (certaian.equals("y"))
                        {
                            System.out.println("已退出零钱通系统");
                            return;
                        }
                        else if (certaian.equals("n"))
                        {
                            System.out.println("已撤回退出操作");
                            break;
                        }
                        else
                        {
                            System.out.println("错误的指令，请重新输入！！！");

                            certaian=myScanner.next();
                        }
                    }
                    break;
                }
                default:
                {
                    System.out.println("错误的指令，请重新输入！！！");
                    break;
                }
            }
        }while(true);
    }
}
