title:"Hi"


a
```javascript {cmd="node"}
const date = Date.now()
console.log(date.toString())
```

```gnuplot {cmd=true output="html"}
set terminal svg
set title "Simple Plots" font ",20"
set key left box
set samples 50
set style data points

plot [-10:10] sin(x),atan(x),cos(atan(x))
```