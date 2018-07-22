The Alif Arabic Programming Language - لغة البرمجة العربية ألف
---------

Official website : [www.aliflang.org](https://www.aliflang.org)

شرح كيفية كتابة مكتبة جديدة بلغة سي بلس بلس و مكتبات wxWidgets
---------

[فيديو الشرح على اليوتوب](https://youtu.be/IEt_cXtx3Vw)

أمثلة بسيطة عن طريقة الدمج بين لغة ألف و لغة سي بلس بلس
---------

*  استعمال متغير من نوع كلمة، داخلة دالة في سي بلس بلس

```
دالة رسالة (كلمة جملة)

_س_
wxMessageBox( @جملة@ );
_س_

نهاية دالة
```

*  استعمال متغير من نوع عدد داخل دالة في سي بلس بلس

```
دالة عدد المجموع (عدد أ، عدد ب)

_س_
double foo;
foo = @أ@ + @ب@;
_س_

رجوع _س_ foo _س_

نهاية دالة
```

*  استعمال دالة سي بلس بلس في لغة ألف

```
_س_

//-- C++ Global Declaration
double GetResult (const double foo, const double bar) {
	return foo + bar;
}

_س_

دالة عدد المجموع (عدد أ، عدد ب)

رجوع _س_ GetResult(@أ@, @ب@) _س_

نهاية دالة
```

والله من وراء القصد

مجتمع ألف
