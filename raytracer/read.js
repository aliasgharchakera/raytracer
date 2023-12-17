const fs = require('fs');

var minX = Infinity;
var minY = Infinity;
var minZ = Infinity;
var maxX = -Infinity;
var maxY = -Infinity;
var maxZ = -Infinity;
var maxPoint = [-Infinity, -Infinity, -Infinity];
var minPoint = [Infinity, Infinity, Infinity];
var maxWidth;
var start_vertice = false;
var vertices = [];
var indexed_vertices = [];
var faces = [];
var numVertices = 0;

const parseFile = (file) => {
    let input = file.toString()
    let lines = input.split('\n')
    for (var i=0; i<lines.length; i++){
        if(start_vertice){
            if(!lines[i].startsWith('3 ')){
                const vertice = lines[i].split(' ')
                const a = Number(vertice[0])
                const b = Number(vertice[1])
                const c = Number(vertice[2])
                const point = [a, b, c];
                vertices.push(point)
                if (isNaN(a) || isNaN(b) || isNaN(c));
                else{
                    minX = Math.min(minX, a);
                    minY = Math.min(minY, b);
                    minZ = Math.min(minZ, c);
                    maxX = Math.max(maxX, a);
                    maxY = Math.max(maxY, b);
                    maxZ = Math.max(maxZ, c);
                }
            }else{
                console.log('faces')
                const face = lines[i].split(' ')
                faces.push(Number(face[1]),Number(face[2]), Number(face[3]))
            }
        }
        if (lines[i].includes('element vertex')){
            numVertices = lines[i].split(' ')[2]
        }
        if (lines[i].includes('end_header')){
            start_vertice = true
        }
    }
    // translating scaling the bunny to the origin
    maxPoint = [maxX, maxY, maxZ]
    minPoint = [minX, minY, minZ]
    const X_width = maxX - minX
    const Y_width = maxY - minY
    const Z_width = maxZ - minZ
    maxWidth = Math.max(X_width, Y_width, Z_width)
    scale = [1/maxWidth, 1/maxWidth, 1/maxWidth];
    translate = [(maxX + minX) / 2,
                (maxY + minY) / 2,
                (maxZ + minZ) / 2]

    //iterating through the faces array to retrieve that index of vertex from the vertices array
    //essentially creating fragments one by one by fetching their respective vertex
    for(var i=0; i<faces.length; i++){
        indexed_vertices.push(vertices[faces[i]])
    }
    colorBunny = [0,1,0];
}

fs.readFile('bunny.ply', (err, data) => {
    if (err) {
        console.error(err);
        return;
    }
    parseFile(data);
});

console.log(faces)