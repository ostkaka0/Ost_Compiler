using Collections = System.Collections.Generic;
using Text = System.Text;


public sealed class Parser
{
    private int index;
    private Collections.IList<object> tokens;
    private readonly Stmt result;

    public Parser(Collections.IList<object> tokens)
    {
        foreach(object t in tokens)
        {
            if (t.ToString() != (new object()).ToString())
                System.Console.Write(t.ToString() + " ");
            else if (t == Scanner.Assign)
                System.Console.Write("= ");
            else
                System.Console.Write(t.GetType().ToString() + " ");
        }
        System.Console.WriteLine();

        this.tokens = tokens;
        this.index = 0;
        this.result = this.ParseStmt(-1);

        if (this.index != this.tokens.Count)
            throw new System.Exception("expected EOF");
    }
    public Stmt Result
    {
        get { return result; }
    }

    private Stmt ParseStmt(int maximumSequences)
    {
        Stmt result;

        if (this.index == this.tokens.Count)
        {
            throw new System.Exception("expected statement, got EOF");
        }

        if (this.tokens[this.index].Equals("print"))
        {
            this.index++;
            Print print = new Print();
            print.Expr = this.ParseExpr();
            result = print;
        }

        else if (this.tokens[this.index].Equals("var"))
        {
            this.index++;
            DeclarVar declareVar = new DeclarVar();

            if (this.index < this.tokens.Count &&
                this.tokens[this.index] is string)
            {
                declareVar.Ident = (string)this.tokens[this.index];

            }
            else
            {
                throw new System.Exception("expected variable name after 'var'");
            }

            this.index++;

            if (this.index == this.tokens.Count ||
                this.tokens[this.index] != Scanner.Assign)
            {
                throw new System.Exception("expected '=' after variable name at " + this.index + " : " + this.tokens.Count);
            }

            this.index++;

            declareVar.Expr = this.ParseExpr();
            result = declareVar;
        }
        else if (this.tokens[this.index].Equals("Parse_obj"))
        {
            this.index++;
            ReadInt readInt = new ReadInt();

            if (this.index < this.tokens.Count &&
                this.tokens[this.index] is string)
            {
                readInt.Ident = (string)this.tokens[this.index++];
                result = readInt;
            }
            else
            {
                throw new System.Exception("expected variable name after 'parse_obj'");
            }
        }
        else if (this.tokens[this.index].Equals("for"))
        {
            this.index++;
            ForLoop forLoop = new ForLoop();

            if (this.index < this.tokens.Count &&
                this.tokens[this.index++] == Scanner.PerenthStart)
            {
                forLoop.Initialization = ParseStmt(1);
                if (forLoop.Initialization is DeclarVar)
                {
                    //delete variable!
                }
            }
            else
            {
                throw new System.Exception("expected '(', got EOF");
            }

            if (this.index < this.tokens.Count
                && tokens[index-1] == Scanner.Semi)
            {
                forLoop.Condition = this.ParseExpr();
            }
            else
            {
                throw new System.Exception("expected ';;' before ')' of for loop");
            }

            this.index++;

            if (this.index < this.tokens.Count
                && tokens[index-1] == Scanner.Semi)
            {
                forLoop.Update = this.ParseStmt(1);
            }
            else
            {
                throw new System.Exception("expected ';' before ')' of for loop");
            }

            if (this.index < this.tokens.Count)
            {
                forLoop.Body = this.ParseStmt(0);
            }
            else
            {

            }

            result = forLoop;
        }
        else if (this.tokens[this.index] is string)
        {
            Assign assign = new Assign();
            assign.Ident = (string)this.tokens[this.index++];

            if (this.index == this.tokens.Count ||
                this.tokens[this.index] != Scanner.Assign)
            {
                throw new System.Exception("expected '=' at " + index.ToString() + " : " + tokens.Count.ToString() + ", got " + this.tokens[this.index].ToString());
            }

            this.index++;

            assign.Expr = this.ParseExpr();
            result = assign;
        }
        else
        {
            throw new System.Exception("parse error at token " + this.index + ": " + this.tokens[this.index]);
        }

        if (this.index < this.tokens.Count &&
            this.tokens[this.index] == Scanner.Semi &&
            maximumSequences != 1)
        {
            this.index++;

            if (this.index < this.tokens.Count &&
                !this.tokens[this.index].Equals("end"))
            {
                Sequence Sequence = new Sequence();
                Sequence.First = result;
                Sequence.Second = this.ParseStmt((maximumSequences == 0)? 0:maximumSequences-1);
                result = Sequence;
            }
            else
            {
                this.index++;
            }
        }

        return result;
    }

    private Expr ParseExpr()
    {
        if (this.index == this.tokens.Count)
        {
            throw new System.Exception("expected expresstion, got EOF");
        }

        else if (this.tokens[this.index] is Text.StringBuilder)
        {
            string Value = ((Text.StringBuilder)this.tokens[this.index++]).ToString();
            StringLiteral StringLiteral = new StringLiteral();
            StringLiteral.Value = Value;
            return StringLiteral;
        }
        else if (this.tokens[this.index] is int)
        {
            int intvalue = (int)this.tokens[this.index++];
            IntLiteral intLiteral = new IntLiteral();
            intLiteral.Value = intvalue;

            if (this.index + 1 < this.tokens.Count)
            {
                if (this.tokens[this.index] is BinOp)
                {
                    BindExpr bindExpr = new BindExpr();
                    bindExpr.Left = intLiteral;
                    bindExpr.Op = (BinOp)this.tokens[this.index];
                    this.index++;
                    bindExpr.right = ParseExpr();

                    if (bindExpr.Left.GetType() == bindExpr.right.GetType())
                    {
                        return bindExpr;
                    }
                    else
                    {
                        throw new System.Exception("cannot bind expression of operation '" +
                            bindExpr.Op.GetType().ToString() +
                            "' between '" +
                            bindExpr.Left.GetType().ToString() +
                            "' and '" +
                            bindExpr.right.GetType().ToString() +
                            "'");
                    }


                }
            }

            return intLiteral;
        }
        else if (this.tokens[this.index] is string)
        {
            Expr expr;

            switch ((string)tokens[this.index])
            {
                case "true":
                    {
                        BoolLiteral boolLiteral = new BoolLiteral();
                        boolLiteral.Value = true;
                        expr = boolLiteral;
                    }
                    break;

                case "false":
                    {
                        BoolLiteral boolLiteral = new BoolLiteral();
                        boolLiteral.Value = false;
                        expr = boolLiteral;
                    }
                    break;

                default:
                    {
                        string Ident = (string)this.tokens[this.index];
                        Variable var = new Variable();
                        var.Ident = Ident;
                        expr = var;
                    }
                    break;
            }

            this.index++;

            if (this.index < this.tokens.Count &&
                this.tokens[this.index] == Scanner.Semi)
            {
                return expr;
            }

            if (this.index + 1 < this.tokens.Count)
            {
                if (this.tokens[this.index] is BinOp)
                {
                    BindExpr bindExpr = new BindExpr();
                    bindExpr.Left = expr;
                    expr = null;
                    bindExpr.Op = (BinOp)this.tokens[this.index];
                    this.index++;
                    bindExpr.right = ParseExpr();

                    if (bindExpr.Left.GetType() == bindExpr.right.GetType())
                    {
                        return bindExpr;
                    }
                    else
                    {
                        throw new System.Exception("cannot bind expression of operation '" +
                            bindExpr.Op.GetType().ToString() +
                            "' between '" +
                            bindExpr.Left.GetType().ToString() +
                            "' and '" +
                            bindExpr.right.GetType().ToString() +
                            "'");
                    }


                }
            }

            return expr;
        }
        else
        {
            throw new System.Exception("expected string literal, int literal, or variable");
        }
    }

}