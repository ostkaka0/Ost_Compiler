using Collections = System.Collections.Generic;
using IO = System.IO;
using Text = System.Text;

public sealed class Scanner
{
    private readonly Collections.IList<object> result;
    public Scanner(IO.TextReader input)
    {
        this.result = new Collections.List<object>();
        this.Scan(input);
    }

    public Collections.IList<object> Tokens
    {
        get { return this.result; }
    }

    #region ArithmithicConstants

    public static readonly object Add = BinOp.Add;
    public static readonly object Sub = BinOp.Sub;
    public static readonly object Mul = BinOp.Mul;
    public static readonly object Div = BinOp.Div;

    public static readonly object Equal = BinOp.Equal;
    public static readonly object Less = BinOp.Less;
    public static readonly object More = BinOp.More;
    public static readonly object LessOrEqual = BinOp.LessOrEqual;
    public static readonly object MoreOrEqual = BinOp.MoreOrEqual;

    public static readonly object Semi = new object();
    public static readonly object Assign = new object();

    public static readonly object PerenthStart = new object();
    public static readonly object PerenthEnd = new object();

    public static readonly object BraceStart = new object();
    public static readonly object BraceEnd = new object();

    public static readonly object SquareStart = new object();
    public static readonly object SquareEnd = new object();

    #endregion

    private void Scan(IO.TextReader input)
    {
        while (input.Peek() != -1)
        {
            char ch = (char)input.Peek();

            if (char.IsWhiteSpace(ch))
            {
                input.Read();
            }
            else if (char.IsLetter(ch) || ch == '_')
            {
                Text.StringBuilder accum = new Text.StringBuilder();
                while (char.IsLetter(ch) || ch == '_')
                {
                    accum.Append(ch);
                    input.Read();

                    if (input.Peek() == -1)
                    {
                        break;
                    }
                    else
                    {
                        ch = (char)input.Peek();
                    }


                }
                this.result.Add(accum.ToString());
            }
            else if (ch == '"')
            {
                Text.StringBuilder accum = new Text.StringBuilder();

                input.Read();

                if (input.Peek() == -1)
                {
                    throw new System.Exception("Unterminated string literal");
                }
                while ((ch = (char)input.Peek()) != '"')
                {
                    accum.Append(ch);
                    input.Read();

                    if (input.Peek() == -1)
                    {
                        throw new System.Exception("Unterminated string literal");
                    }

                }
                input.Read();
                this.result.Add(accum);
            }
            else if (char.IsDigit(ch))
            {
                Text.StringBuilder accum = new Text.StringBuilder();

                while (char.IsDigit(ch))
                {
                    accum.Append(ch);
                    input.Read();

                    if (input.Peek() == -1)
                    {
                        break;
                    }
                    else
                    {
                        ch = (char)input.Peek();
                    }
                }
                this.result.Add(int.Parse(accum.ToString()));
            }
            else
            {
                input.Read();

                switch (ch)
                {
                    case '+':
                        this.result.Add(Scanner.Add);
                        break;

                    case '-':
                        this.result.Add(Scanner.Sub);
                        break;

                    case '*':
                        this.result.Add(Scanner.Mul);
                        break;

                    case '/':
                        this.result.Add(Scanner.Div);
                        break;

                    case ';':
                        this.result.Add(Scanner.Semi);
                        break;

                    case '=':
                        if (input.Peek() == '=')
                        {
                            input.Read();
                            this.result.Add(Scanner.Equal);
                        }
                        else
                        {
                            this.result.Add(Scanner.Assign);
                        }
                        break;

                    case '<':
                        if (input.Peek() == '=')
                        {
                            input.Read();
                            this.result.Add(Scanner.LessOrEqual);
                        }
                        else
                        {
                            this.result.Add(Scanner.Less);
                        }
                        break;

                    case '>':
                        if (input.Peek() == '=')
                        {
                            input.Read();
                            this.result.Add(Scanner.MoreOrEqual);
                        }
                        else
                        {
                            this.result.Add(Scanner.More);
                        }
                        break;

                    case '(':
                        this.result.Add(PerenthStart);
                        break;

                    case ')':
                        this.result.Add(PerenthEnd);
                        break;

                    case '{':
                        this.result.Add(BraceEnd);
                        break;

                    case '}':
                        this.result.Add(BraceEnd);
                        break;

                    case '[':
                        this.result.Add(SquareEnd);
                        break;

                    case ']':
                        this.result.Add(SquareEnd);
                        break;

                    default:
                        System.Console.WriteLine("WTF " + ch);
                        break;
                }
            }
        }
    }

}