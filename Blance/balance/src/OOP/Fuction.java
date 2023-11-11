package OOP;

import java.text.SimpleDateFormat;
import java.util.Date;
import java.util.Scanner;

public class Fuction
{

    double total,balance;
    Date date=null;
    SimpleDateFormat std=new SimpleDateFormat("yyyy-MM-dd  HH:mm");
    String detail=null;
    String note="";
    String certaian="n";
    String userName;
    Scanner myScanner= new Scanner(System.in);

    public Fuction(String userName) {
        this.userName = userName;
    }

    public void details()
    {
        if (detail==null)
        {
            System.out.println("你的账户没有任何交易信息");
        }
        else
        {
            System.out.println(this.detail);
        }
    }

    public void income()
    {
        System.out.print("请输入收入金额：");

        while (true) {
            balance = myScanner.nextDouble();
            if (balance >= 100000) {
                System.out.println("系统警告，操作数额过大，可能涉及洗钱，请联系客服证明资产来源后再存入");
                System.out.println("本次未收入到你的账户，请输入合法金额后再试一次");
            } else {
                date = new Date();
                total += balance;
                if (detail==null)
                {
                    detail= "收入：+" + balance + "\t" + std.format(date) + "\t余额为：" + total+"\n";
                }
                else
                {
                    detail += "收入：+" + balance + "\t" + std.format(date) + "\t余额为：" + total+"\n";
                }


                break;
            }
        }
    }

    public void pay()
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
        detail+="支出："+"-"+balance+"\t"+std.format(date)+"\t余额为"+total+"\t用处："+note+"\n";
    }

    public String exit()
    {
        System.out.println("确定要退出系统吗？y/n");
        certaian=myScanner.next();
            if (certaian.equals("y")) {
                System.out.println("已退出零钱通系统");
            } else if (certaian.equals("n")) {
                System.out.println("已撤回退出操作");
            } else {
                System.out.println("错误的指令，请重新输入！！！");

                certaian = myScanner.next();
            }
        return certaian;
    }

}
