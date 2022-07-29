# 					零知识证明--英语成绩

平台：Linux

语言：circom

运行环境：curl，g++，gcc，snarkjs，circom，cargo, circomlib, npm, nodejs

Author：张浩旸

日期：2022/7/29

成功运行截图：

![IMG_0803(20220725-184209)](C:\Users\ASUS\Documents\Tencent Files\8915384\FileRecv\MobileFile\IMG_0803(20220725-184209).PNG)



运行指南：

1.首先新建一个文件：`mkdir InRange.circom`

文件内容:

~~~
pragma circom 2.0.0;
include "./circomlib/circuits/comparators.circom";
include "./circomlib/circuits/bitify.circom";
template InAuthorizedRange()
{
	signal input min_grade;
	signal input your_grade;
	signal output out;
	component gt=GreaterEqThan(9);
	gt.in[0] <== your_grade;
	gt.in[1] <== min_grade;
	gt.out === 1;
	out <--gt.out;
	out === 1;
}

component main = InAuthorizedRange();
~~~

这是circom的电路约束文件

2.接下来安装依赖软件：

`sudo apt-get install curl g++ gcc cargo npm nodejs`

`sudo npm install -g snarkjs`

请注意circom在2021年某次更新后已经无法使用npm安装，需要手动git clone并且编译（我上个学期还可以）

3.安装circom：

`curl --proto '=https' --t1sv1.2 https://sh.rustup.rs -sSf | sh`

`git clone https://github.com/iden3/circom.git`

`cargo build --release`

`cargo install --path circom`

以上都正常完成后，输入help指令应该可以看到circom的提示界面

`circom --help`

此时说明安装完成



4.编译电路

`circom InRange.circom --r1cs --wasm --sym --c`

`--r1cs` 生成 `InRange.r1cs`文件，包含了该电路的R1CS约束系统

`--wasm`生成 `InRange_js`文件夹，包含了`Wasm`代码以及其他需要的用来生成witness的文件

`sym`生成`InRange.sym`文件，是circom的符号表文件

`--c`生成`InRange.cpp`文件，用于后续编译

![IMG_0797](C:\Users\ASUS\Documents\Tencent Files\8915384\FileRecv\MobileFile\IMG_0797.PNG)

5.计算witness

新建文件 `sudo touch input.json && chomod 666 input.json `

文件中给出输入`{"your_grade":625,"min_grade":425}`

用WebAssembly计算witness:`node generate_witness.js InRange.wasm input.json witness.wtns`

![IMG_0796(20220725-184206)](C:\Users\ASUS\Documents\Tencent Files\8915384\FileRecv\MobileFile\IMG_0796(20220725-184206).PNG)

上一条指令执行前应当将输入文件放入正确的文件夹中



6.证明

`snarkjs powersoftau new bn128 12 pot12_0000.ptau -v`

![IMG_0799](C:\Users\ASUS\Documents\Tencent Files\8915384\FileRecv\MobileFile\IMG_0799.PNG)

`snarkjs powersoftau contribute pot12_0000.ptau pot12_0001.ptau --name="First contribution -v"`

![IMG_0798](C:\Users\ASUS\Documents\Tencent Files\8915384\FileRecv\MobileFile\IMG_0798.PNG)

`snarkjs powersoftau prepare phase pot12_0001.ptau pot12_final.ptau -v`

![IMG_0800](C:\Users\ASUS\Documents\Tencent Files\8915384\FileRecv\MobileFile\IMG_0800.PNG)

`snrakjs zkey contribute InRange_0000.zkey InRange_0001.zkey --name="1 st "`

![IMG_0801(20220725-184208)](C:\Users\ASUS\Documents\Tencent Files\8915384\FileRecv\MobileFile\IMG_0801(20220725-184208).PNG)



导出验证密钥：

`snarkjs zkey export verificationkey InRange_0001.zkey verification_key.json`

生成证明

`snarkjs groth16 prove InRange_0001.zkey witness.wtns proof.json public,json`

![IMG_0802(20220725-184208)](C:\Users\ASUS\Documents\Tencent Files\8915384\FileRecv\MobileFile\IMG_0802(20220725-184208).PNG)

验证证明：

`snarkjs groth16 verify verification_key.json public.json proof.json`

![IMG_0803(20220725-184209)](C:\Users\ASUS\Documents\Tencent Files\8915384\FileRecv\MobileFile\IMG_0803(20220725-184209).PNG)

由此得到上述截图中验证通过的结果，OK代表验证通过（因为之前给出的your_grade是625大于min_grade 425）

工程文件中的circomlib是circom官方提供的工具包，下载后放在工程文件的根目录即可
