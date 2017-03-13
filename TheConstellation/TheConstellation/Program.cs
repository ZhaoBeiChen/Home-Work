using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Threading.Tasks;

namespace TheConstellation
{
    class Program
    {
        static void Main(string[] args)
        {
            Interface pro = new Interface();
            
        }
    }

    class Interface
    {
        static void MainInterface()
        {
            Console.WriteLine("|-<[欢迎使用星座查询程序]>-|");
            Console.WriteLine("【输入数字1】开始星座查询");
            Console.WriteLine("【输入数字2】退出程序");
        }

        void RunMainInterface()
        {
            while (true)
            {
                MainInterface();
            }
        }
    }
}
