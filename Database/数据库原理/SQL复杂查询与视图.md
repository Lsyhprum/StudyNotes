# 子查询

出现在 WHERE 子句中的 SELECT 语句称为 子查询,用于解决：

* 集合成员资格（IN）
* 集合之间比较（theta some / theta all)
* 集合基数测试（EXISTS)

## IN / NOT IN

判断某一表达式的值是否在子查询结果中

```sql
SELECT * FROM Stu WHERE Sname in ();
```


## theta some / theta all

eg: 找出工资最低的教师姓名

```sql
Select Tname From Teacher WHERE Salary <= all (Select Salary From Teacher);
```

eg：找出001号课程成绩不是最高的所有学生学号

```sql
SELECT S# FROM SC
WHERE C#="001" AND Score < some(SELECT Score FROM SC WHERE C#="001");
```

**表达式 = some(子查询)  ==   表达式 in (子查询)**

**表达式 <> all(子查询) ==  表达式 not in (子查询)**

## EXISTS

子查询结果中有无元组存在，用于检索 **全部**

eg：检索学过1号讲师主讲的所有课程的所有同学的姓名

```sql
SELECT Sname FROM Student
WHERE not exists
    （SELECT * FROM Course
        WHERE Course.T# == '001' and not exists
            (SELECT * FROM SC
                WHERE S# = Student.S# and C# = Course.C#));
```
不存在有一门 001 号教师主讲的课程该同学没学过

# 结果计算与聚集函数

SELECT 子句可以是列名，也可以是 **计算表达式、聚集函数**

聚集函数：

* COUNT
* SUM
* AVG
* MAX
* MIN

# 分组查询与分组过滤

SQL 将检索到的元组按某一条件进行分类，具有相同条件值的元组划到一个组或一个集合中，同时处理多个组或集合的聚集运算

eg:求每一门课程的平均课程

```sql
SELECT C# , AVG (Score) FROM SC Group by C#;
```

错误写法：

求不及格课程超过两门的同学的学号

```sql
SELECT S# FROM SC
WHERE Score < 60 and Count(*) > 2
GROUP BY S#;
```

**聚集函数不允许用于 WHERE 子句中**, **WHERE 是对每一元组进行条件过滤**

```sql
SELECT S# FROM SC
WHERE Score < 60
GROUP BY S# Having Count(*) > 2;
```

# 关系代数操作

## 并-交-差处理

```SQL
子查询 {Union(ALL) | INTERSECT [ALL] | Except [ALL]} 子查询
```

通常情况下自动删除重复元组，若保留重复元组，要带 ALL

eg:

求学过 2 号课或学过 3 号课同学的学号

```sql
SELECT S# FROM SC WHERE C# = '002'
UNION
SELECT S# FROM SC WHERE C# = '003';
```

## 空值

eg:找出年龄值为空的学生姓名

```sql
SELECT Sname From Student
WHERE Sage is null;
```

**空值不能运算**，Sage=null 错误

## 内连接/外连接


# 视图

概念模式 -> 基本表
外模式 + EC Mapping -> 视图

## 定义视图

```sql
CREATE VIEW VIEW_NAME (COL, COL,...)    ---> 外模式
    AS 子查询 ()                        ----> EC Mapping
```

## 更新问题

视图不保存数据，不一定能成功更新数据

* 包含聚集函数，不能更新
* 使用 UNIQUE 或 DISTINCE ，不能更新
* GROUP BY ，不能更新
* 算术表达式计算出的列，不能更新
* 缺失主键，不能更新


# 小结

* SQL 查询
  * 子查询：SELECT IN theta some/all EXISTS GROUP BY HAVING
  * 关系代数实现
* 视图