using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;

namespace compiler_test_real
{
    class Program
    {
        static void Main(string[] args)
        {
            if (args.Length != -1)
            {
                Console.WriteLine("Press enter to compiler your code.");
                Console.ReadLine();
                Console.WriteLine("Compiling...");
                try
                {
                    Console.WriteLine("a");
                    Scanner Scanner = null;
                    using (TextReader input = File.OpenText(args[0]))
                    {
                        Console.WriteLine("b");
                        Scanner = new Scanner(input);
                    }

                    Console.WriteLine("c");
                    Parser Parser = new Parser(Scanner.Tokens);

                    Console.WriteLine("d");
                    CodeGen CodeGen = new CodeGen(Parser.Result, Path.GetFileNameWithoutExtension(args[0]) + ".exe");
                    Console.WriteLine("e");
                }
                catch (Exception e)
                {
                    Console.Error.WriteLine(e.Message);
                }
                finally
                {
                    Console.WriteLine("Compilled!");
                }
            }

            Console.ReadLine();

        }
    }
}
