# O(logn!)=O(nlogn)
我们可以证明logn！小于nlogn而大于一个常数倍的nlogn。<br>
下面给出推导过程：<br>
对于n>0，显然logn！<=nlogn是显然成立的<br>
![](https://img-blog.csdnimg.cn/20200604222939384.gif)<br>
接下来，证明logn！>=Cnlogn<br>
![](https://img-blog.csdnimg.cn/20200604223223385.gif)<br>
我们去掉前半部分，则可得:<br>
![](https://img-blog.csdnimg.cn/20200604223604357.gif)<br>
取最小项替代所有项，则：<br>
![](https://img-blog.csdnimg.cn/20200604224522488.gif)<br>
由于小于n/2logn，我们可以取其大于1/4logn:<br>
![](https://img-blog.csdnimg.cn/20200604225253483.gif)<br>
完整的步骤：<br>
![](https://img-blog.csdnimg.cn/202006042256202.gif)<br>
所以<br>
![](https://img-blog.csdnimg.cn/20200604225802977.gif)<br>
O(lgn!)=O(nlogn)证毕
