##Python client bot

In order to use the client bot, open a python 2.7 console here and use  
```python
execfile('client.py')
```
From there you can still send messages by using
```python
s.send('MESSAGE')
```  
You can flush the received data by using either
```python
dump_data(s)
```
or
```python
loop_dump_data(s)
```
