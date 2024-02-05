const express = require('express');
const exec = require('child_process').exec;
const path = require('path');
const app = express();
const port = 5305;


app.use(express.static(path.join(__dirname,'../webPage')));

app.get('/', (req, res) => {
    res.sendFile(path.join(__dirname,'../webPage/html/index.html'));
});
 
app.get('/controlLed', (req) => {
    const command = req.query.command;
    const shellControlScript = exec(`led ${command}`);
    
    shellControlScript.stdout.on('data', (data)=>{
        res.send(`Command executed: ${command}`); 
    });

    shellControlScript.stderr.on('data', (data)=>{
        res.status(500).send(`Error executing command: ${command}`);
    });
});

// Start the server
app.listen(port, () => {
    console.log(`Server is running at http://localhost:${port}`);
});      