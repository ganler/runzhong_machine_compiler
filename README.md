# RunzhongMachineCompiler

## Author Info

> - Jiawei Liu@ganler
>   - Project Manager;
>   - CXX backend building;
>   - Algorithm;
> - Junyao Li@taltalite
>   - React Frontend;
> - Zizheng Zhong@zzznb
>   - Algorihtm.

## Demo

### Lexcial GUI

![](image/lexviz.png)

### Syntax GUI

![](image/synviz-1.png)

![](image/synviz-2.png)

## Build CXX

> As I am a modern C++ programmer, you may need to upgrade your compiler to support C++17.
>
> > `std::string_view` will boost the performance of your application!

![](image/buildcxx.png)

## Build React

> Make sure that `node.js` is installed on your computer.

```shell
mv parse_tree ../parse_tree
mv lexcial ../lexcial

npx create-react-app parse_tree # long time to install react components
npx create-react-app lexcial

cp -r ../parse_tree/ parse_tree/
cp -r ../lexcial/ lexcial/

cd lexcial
npm install typescript
unset HOST
npm start # then you gonna see them.

cd ../parse_tree
npm install d3
npm install antd
unset HOST
npm start # then you gonna see a parse-tree. Wonderful!
```

## Lexcial & Syntax Analysis

![](image/show.jpg)

## Brief Intro to Our Design

![](https://i.loli.net/2019/10/22/tM4EFS1PVpQDHce.png)

![](https://i.loli.net/2019/10/22/tpF21hsnNQTOR7k.png)

![](https://i.loli.net/2019/10/22/UYFRBH7djCk3rsu.png)



## TODO

- Upload our report(More tech details)