public abstract class Stmt
{
}

public class DeclarVar : Stmt
{
    public string Ident;
    public Expr Expr;
}

public class Print : Stmt
{
    public Expr Expr;
}

public class Assign : Stmt
{
    public string Ident;
    public Expr Expr;
}

public class ForLoop : Stmt
{
    public Stmt Initialization;
    public Expr Condition;
    public Stmt Body;
    public Stmt Update;
}

public class ReadInt : Stmt
{
    public string Ident;
}

public class Sequence : Stmt
{
    public Stmt First;
    public Stmt Second;
}

public abstract class Expr
{
}

public class StringLiteral : Expr
{
    public string Value;
}

public class IntLiteral : Expr
{
    public int Value;
}

public class BoolLiteral : Expr
{
    public bool Value;
}

public class BindExpr : Expr
{
    public Expr Left;
    public Expr right;
    public BinOp Op;
}

public class Variable : Expr
{
    public string Ident;
}

public enum BinOp
{
    Add,
    Sub,
    Mul,
    Div,
    Equal,
    More,
    Less,
    MoreOrEqual,
    LessOrEqual,
}

public class PauseObj : Stmt
{
    public string Ident;
}