client = new $.RestClient('http://karlduino3.local/arduino/robot/')
client.add("forward")
client.add("backward")
client.add("stop")
client.add("right")
client.add("left")

color = "slateblue"
hilit = "Orchid"
gapx = 5
gapy = 5
rw = 150
rh = 50
bev = 10
w = gapx*4+rw*3
h = gapy*4+rh*3

    
svg = d3.select("div#for_svg")
        .append("svg")
        .attr("height", h)
        .attr("width", w)

y = [gapy,
     gapy*2+rh, gapy*2+rh, gapy*2+rh,
     gapy*3+rh*2]
x = [gapx+rw,
     0, gapx+rw, gapx*2+rw*2,
     gapx+rw]
lab = ["forward", "left", "stop", "right", "backward"]

# rectangles
svg.selectAll("empty")
  .data(lab)
  .enter()
  .append("rect")
  .attr("id", (d) -> d)
  .attr("fill", (d) ->
      return color if d != "stop"
      hilit)
  .attr("x", (d,i) -> x[i])
  .attr("y", (d,i) -> y[i])
  .attr("height", rh)
  .attr("width", rw)
  .attr("rx", bev)
  .attr("ry", bev)
  .attr("stroke", color)
  .attr("stroke-width", "3")
  .on("click", (d) ->
      d3.selectAll("rect").attr("fill", color)
      d3.select(this).attr("fill", hilit)
      client.forward.read() if d=="forward"
      client.backward.read() if d=="backward"
      client.stop.read() if d=="stop"
      client.left.read() if d=="left"
      client.right.read() if d=="right"
      )
  .on("touchstart", (d) ->
      d3.selectAll("rect").attr("fill", color)
      d3.select(this).attr("fill", hilit)
      client.forward.read() if d=="forward"
      client.backward.read() if d=="backward"
      client.stop.read() if d=="stop"
      client.left.read() if d=="left"
      client.right.read() if d=="right"
      )
   .on("mouseover", (d) ->
       d3.select(this).attr("stroke", hilit))
   .on("mouseout", (d) ->
       d3.select(this).attr("stroke", color))

# text
svg.selectAll("empty")
  .data(lab)
  .enter()
  .append("text")
  .attr("fill", "white")
  .style("font-size", "30px")
  .text((d) -> d)
  .attr("x", (d,i) -> x[i]+rw/2)
  .attr("y", (d,i) -> y[i]+rh/2)
  .attr("dominant-baseline", "middle")
  .attr("text-anchor", "middle")
  .style("pointer-events", "none")

