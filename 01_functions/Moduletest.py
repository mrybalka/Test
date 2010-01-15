#--*-- encoding: utf-8 --*--
'''
Created on 22.12.2009

@author: Masha
'''

#форматирование строк
print "Hello, world" 
print "First, thou shalt count to {0}".format('hello') # References first positional argument
print "My quest is {name}".format(name='My')             # References keyword argument 'name'
ARG ={1:'1',2:'2',3:'3',4:'4'}
print "hello my %s litle friend" % (ARG,)

x = {
     'source': 'Library',
     'module': 'foo',
     'arg': 'xxx',
}

"Imported xxx from Library:foo"
print "Imported %(arg)s from %(source)s:%(module)s"  % x

def file_to_list(filename):
    return [
        tuple([j.rstrip() for j in i.split(':')])
        for i in open(filename)
    ]

print file_to_list('test.txt')        
#filename = raw_input('Give file name:')            
#print file_to_list(filename)  

#считывание из файла, строки через : с распознованием типа
def file_to_list2(filename):
    res = []
    for i in open(filename):
        #
        # Review: tmp_list плохое имя
        #
        tmp_list = []
        for j in i.split(':'):
            #
            # Review: почему только .rstrip()? а не .strip()?
            #
            if j.rstrip().isdigit():
                #
                # Review: внутри int() strip() не нужен
                #
                tmp_list.append(int(j.rstrip()))
            else: 
                tmp_list.append(j.rstrip())
        res.append(tuple(tmp_list))
    return res


def better_ftl2(fname):
    """
    More Pythonic version of file_to_list2
    """
    converters = {
        # key is boolen for .isdigit(), value is action
        True: int,
        False: str.strip,
    }
    res = []
    for xline in open(fname):
        record = []
        for element in xline.split(':'):
            is_digit = element.isdigit()
            action = converters[is_digit]
            record.append(action(element))
        ## или то же самое, но в более короткой форме, с использованием
        ## generator expression внутри tuple()
        # record = tuple(converters[x.isdigit()](x) for x in xline.split(':'))
        res.append(tuple(record))
    return res

print file_to_list2('test.txt')        


#1
L=[1,2,3]
print dir(L)
#2
public_methods = [attr for attr in dir(L) if  attr[:1]=='_']
print public_methods

#3
methodList = [method for method in dir(L) if callable(getattr(L, method))]
print methodList

#4 
#5
T1 = (1,2,3,4,5)
T2 = (3,4,5,6,7,8)
T3 = T1 + T2
print T3
#6
print "Задание 6 способ 1"
T3 = T1 + tuple([t for t in T2 if t not in T1])
T3 = tuple([t for t in T1 if t not in T2]) + tuple([t for t in T2 if t not in T1])
print T3

print "Задание 6 способ 2"
M = set(T1)
L = set(T2)
T3 = tuple(M |((M | L) - (M & L)))
T3 = tuple((M | L) - (M & L))
print T3 

#8
Lkeys = ['source', 'module', 'arg']
Lvalues = ['library','foo','xxx']
D = dict(zip(Lkeys,Lvalues))
print D


#9
Lkeys=['source','module','arg', 'keywords']
Lvalues=['library','foo','xxx']
#Lkeys=['source','module']
#Lvalues=['library','foo','xxx']
D=dict(map(None,Lkeys,Lvalues))
print D

#10
print 'задание 10'
D2 = dict(zip(D.values(),D.keys()))
print D2

print 'второй способ'
D2 = {}
for (x,y) in D.items(): D2[y]=x
print D2

print 'третий способ'
D2 = dict([(x,y) for y,x in D.items()])
print D2

#11
unicode_string = u"hello"
print type(unicode_string)
utf_string = unicode_string.encode("utf-8")
print type(utf_string)
cp_string = unicode_string.encode("cp1251")
print type(cp_string)

#12 
cp_string = 'hello'
print type(cp_string)
unicode_string = cp_string.decode("cp1251")
print type(unicode_string)


#
# Review: перечитай и ИСПОЛЬЗУЙ PEP-8. Следующий раз заставлю весь код
# переделывать согласно PEP-8
#

# Декоратор
def decor(f):
    cache = {}
    def helper(x,y):
        if (x,y) not in cache:
            cache[(x,y)] = f(x,y)
        return cache[(x,y)]
    return helper


def common_decor(f):
    cache = {}
    def tmp(*args, **kwargs):
        #
        # Review: tuple для словаря не годится, придумай что-нибудь еще
        # >>> tuple({'a': 'b', 'c': 'd'})
        # <<< ('a', 'c')
        # >>> tuple({'a': 'b', 'c': 'x'})
        # <<< ('a', 'c')
        #
        elem = args+ tuple(kwargs)
        if elem not in cache:
            cache[elem] = f(*args, **kwargs)
        return cache[elem]
    return tmp

@common_decor
def add(x,y,z):
    print x, '+', y, '+', z
    return x+y+z
    
print add(1,2,3)
print add(2,3,5)
print add(1,2,3)
print 'Привет!!' #проверка кодировки

#1. Написать функцию, которой можно передавать аргументы либо списком/кортежем,
#   либо по одному. Функция производит суммирование всех аргументов.

#>>> f(1, 2, 3)  # вернет 1 + 2 + 3 = 6
#>>> f([1, 2, 3]) # вернет 1 + 2 +3 = 6
#>>> f((3, 5, 6)) # вернет 3 + 5 + 6 = 14

#2. Написать функцию-фабрику, которая будет возвращать функцию сложения с
#   аргументом. Например, 
#>>> add5 = addition(5) # функция addition возвращает функцию сложения с 5
#>>> add5(3) # вернет 3 + 5 = 8
#>>> add5(8) # вернет 8 + 5 = 13

#>>> add8 = addition(8)
#>>> add8(2) # вернет 2 + 8 = 10
#>>> add8(4) # вернет 4 + 8 = 12

#Написать варианты с обычной "внутренней" и анонимной lambda-функцией.

#3. Написать фабрику, аналогичную п.2, но возвращающей список таких функций
#>>> additionals = addition_range(0, 5) # список из функций сложения от 0 до 5 включительно

#т.е. аналогичное [add0, add1, add2, add3, add4, add5]

#4. Написать аналог map:
# - первым аргументом идет либо функция, либо список функций
# - вторым аргументом -- список аргументов, которые будут переданы функциям
# - полагается, что эти функции -- функции одного аргумента

#т.е. mymap([add0, add1, add2], [1, 2, 3]) должно вернуть
#[(1, 2, 3), (2, 3, 4), (3, 4, 5)], в данном случае "развернутая" запись будет:
#[(add0(1), add0(2), add0(3)), (add1(1), add1(2), add1(3)), (add2(1), add2(2), add2(3))

#1
def myadd(*args):
    sum = 0
    if len(args)==1:
        for item in args:
            for x in item:
                sum += x
    else:
        for x in args: sum +=x  
    return sum

print myadd((1,2,3))

# Review: а теперь сделай myadd(1, 2, [3, 4], 5) и оно должно просуммировать 1, 2, 3, 4, 5

#2 
def addition(N):
    def tmp(x):
        print "%s + %s = %s" % (x, N, x+N)
        #
        # Review: забыла return
        #
    return tmp

add5 = addition(5)
add5(1)
add5(2)

add8 = addition(8)
add8(1)
add8(6)

    
def addition_lambda(N):
    return(lambda x: x+N)
   
add5 = addition_lambda(5)
print add5(1)
print add5(2)

#3
def addition_range(low_bound, high_bound):
    res=[]
    #
    # Review: верхняя граница ВКЛЮЧИТЕЛЬНО
    # плюс xrange лучше range, скажи почему :)
    #
    for i in range(low_bound, high_bound):
        #
        # Review: за i=i молодец, откуда узнала?
        #
        res.append(lambda x, i=i: x+i)
    return res

additionals = addition_range(0,5)
print additionals[3](4) 

#4     
def mymap(list_func, list_arg):
    res = []
    #
    # Review: цикл не несет функциональности, попробуй сделать при помощи
    # list comrehension
    #
    for f in list_func:
        tp = ()
        #
        # Review: цикл лишний, сделай с помощью generator expression
        #
        for a in list_arg:
            tp = tp+(f(a),)
        res.append(tp)
    return res

print mymap(additionals, [1,2,3,4])   
