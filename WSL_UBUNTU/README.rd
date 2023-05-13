### [ubuntu20.04 under WIN10](https://github.com/xiaolaba/Win10_install_Ubuntu): (xiaolaba, 2021-JAN-04)
```
sudo apt-get install libboost1.65-dev libboost-filesystem1.65-dev qtbase5-dev libqt5x11extras5-dev libsqlite3-dev
git clone https://github.com/xiaolaba/AlphaDict
```


How to Compile
==============
(xiaolaba, 2021-JAN-04)
```
$ cd ~/AlphaDict/src 
```

linux,unix
----------
```
$ ./configure  
$ ./configure --help
  can give you some useful information, if you get trouble and want to set some 
  custom configurations to fix it.

$ make 

$ make install

$ AlphaDict
  Now, You can enjoy 'AlphaDict'. 

$ make uninstall

$ make uitr
  make muti-language.
```   

### configure ok
![alphadict_config_ok.JPG](alphadict_config_ok.JPG)  
### make error
![alphadict_make_error.JPG](alphadict_make_error.JPG)  

