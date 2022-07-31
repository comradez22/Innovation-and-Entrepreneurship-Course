项目15:发送一-个tx在比特币测试网，并解析x数据到 每- -位，更好地写脚本自己 

完成人：张施珵

运行方法：直接运行main.py


实验要求：在bitcoin的测试网站上发布一个交易记录，然后把他的记录爬取下来

步骤：先创建一个测试交易地址
<img width="1090" alt="截屏2022-07-28 21 17 34" src="https://user-images.githubusercontent.com/108727329/181522481-68ce3063-82e8-4f44-9c6d-775b6712da1c.png">

然后获取一些bitcoin
<img width="1165" alt="截屏2022-07-28 21 37 49" src="https://user-images.githubusercontent.com/108727329/181522599-3b468ee0-75bf-400f-a85e-e310152587ea.png">

到blockcryher这个网站上看一下交易的记录
<img width="1140" alt="截屏2022-07-28 21 40 11" src="https://user-images.githubusercontent.com/108727329/181522899-192e360b-27f1-4e83-809e-7cec9d714baf.png">

具体的记录

<img width="1217" alt="截屏2022-07-28 21 40 18" src="https://user-images.githubusercontent.com/108727329/181523319-7378df23-1bca-4f7b-8f41-55a7a8436ec6.png">

https://api.blockcypher.com/v1/btc/test3/txs/44b0e7aef67bd56f35e34ef62275883b19378d448b9050b91b35603f3a3040dc?limit=50&includeHex=true

然后我们用request模块直接把它爬取下来得到tx .txt文档

{
  "block_height": -1,
  "block_index": -1,
  "hash": "44b0e7aef67bd56f35e34ef62275883b19378d448b9050b91b35603f3a3040dc",
  "hex": "020000000001011ba9f5937727c1b08a38790380518dbeb5e389a9c38352ed1848de822decc65e0000000000feffffff025449035b000000001976a914c8b2dec2d91f69cf52a94048e9c5722e67022fb988acd1910f00000000001976a9142298332346be652cce0e0b2740f2c4b55de1bf4588ac024730440220783341f66f0a03c6ab2ecc6cdc38408352aec2ec612b760cca2861a70a78306c022025c4a39f4c0bc04b90c2fa0fd5f7bcae6bf147af9bb88985e2007912350dd76201210382689e12a729be88eaa6326d4b52707622dccca063aeb240eac56fce86618cd9a8432300",
  "addresses": [
    "mifsbboEK2wCh1EM1qLbm21Jsr9mRQNXbd",
    "myp9iY5sHX7CHiwF7jSoUKxLjREppyRHq2",
    "tb1qzs8084uanckr59cm0am7fefad28mkzhjupfp5d"
  ],
  "total": 1527962405,
  "fees": 73540,
  "size": 228,
  "vsize": 147,
  "preference": "high",
  "relayed_by": "54.84.85.20:18333",
  "received": "2022-07-28T13:18:34.043Z",
  "ver": 2,
  "lock_time": 2311080,
  "double_spend": false,
  "vin_sz": 1,
  "vout_sz": 2,
  "confirmations": 0,
  "inputs": [
    {
      "prev_hash": "5ec6ec2d82de4818ed5283c3a989e3b5be8d51800379388ab0c1277793f5a91b",
      "output_index": 0,
      "output_value": 1528035945,
      "sequence": 4294967294,
      "addresses": [
        "tb1qzs8084uanckr59cm0am7fefad28mkzhjupfp5d"
      ],
      "script_type": "pay-to-witness-pubkey-hash",
      "age": 0,
      "witness": [
        "30440220783341f66f0a03c6ab2ecc6cdc38408352aec2ec612b760cca2861a70a78306c022025c4a39f4c0bc04b90c2fa0fd5f7bcae6bf147af9bb88985e2007912350dd76201",
        "0382689e12a729be88eaa6326d4b52707622dccca063aeb240eac56fce86618cd9"
      ]
    }
  ],
  "outputs": [
    {
      "value": 1526942036,
      "script": "76a914c8b2dec2d91f69cf52a94048e9c5722e67022fb988ac",
      "addresses": [
        "myp9iY5sHX7CHiwF7jSoUKxLjREppyRHq2"
      ],
      "script_type": "pay-to-pubkey-hash"
    },
    {
      "value": 1020369,
      "script": "76a9142298332346be652cce0e0b2740f2c4b55de1bf4588ac",
      "addresses": [
        "mifsbboEK2wCh1EM1qLbm21Jsr9mRQNXbd"
      ],
      "script_type": "pay-to-pubkey-hash"
    }
  ]
}


首先核对交易的地址：就是mifsbboEK2wCh1EM1qLbm21Jsr9mRQNXbd是我之前创建的测试地址

其中包含的内容：hash值，交易的地址，交易的总数，给矿工的费用，收到的时间就是7-28日当天，接下是

input，input里面有签名，并且指向使用哪个交易的output

output包含value也包含了接收方的地址
