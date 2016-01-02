client = new $.RestClient('http://karlduino3.local/arduino/robot/')
client.add("forward")
client.add("backward")
client.add("stop")
client.add("right")
client.add("left")

$("#Forward").click () -> client.forward.read()
$("#Stop").click () -> client.stop.read()
$("#Backward").click () -> client.backward.read()
$("#Left").click () -> client.left.read()
$("#Right").click () -> client.right.read()

w = window
d = document
e = d.documentElement
g = d.getElementsByTagName('body')[0]
w = w.innerWidth || e.clientWidth || g.clientWidth
h = w.innerHeight|| e.clientHeight|| g.clientHeight
w = 300 if w > 300
h = 300 if h > 300
    
svg = d3.select("div#for_svg")
        .append("svg")
        .attr("height", h)
        .attr("width", w)
svg.append("rect").attr("height", h).attr("width", w).attr("x", 0).attr("y",0).attr("fill", "#ccc")
