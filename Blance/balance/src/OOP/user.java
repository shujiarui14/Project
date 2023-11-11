package OOP;

public class user extends Fuction{
    String option="";
    public  user(String userName)
    {
        super(userName);
        while (true)
        {
            System.out.println("--------------"+userName+"的零钱通账户-------------");
            System.out.println("----------------1、查看流水----------------");
            System.out.println("----------------2、收入-------------------");
            System.out.println("----------------3、支出-------------------");
            System.out.println("----------------4、退出系统----------------");
            System.out.print("请输入对应操作");

            option=myScanner.next();
            switch (option)
            {
                case "1":
                {
                    super.details();
                    break;
                }
                case "2":
                {
                    super.income();
                    break;
                }
                case "3":
                {
                    super.pay();
                    break;
                }
                case "4":
                {
                    String judg=super.exit();
                    while (true)
                    {
                        if (judg.equals("y"))
                        {
                            return;
                        }
                       else if (judg.equals("n"))
                        {
                            break;
                        }
                       else
                        {
                            judg=super.exit();
                        }
                    }

                }
            }
        }
    }
}
