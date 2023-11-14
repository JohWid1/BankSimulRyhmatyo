const mysql = require('mysql2');
const connection = mysql.createPool({
  host: 'localhost',
  user: 'peppiuser',
  password: 'peppipass',
  database: 'mydb'
});
module.exports = connection;