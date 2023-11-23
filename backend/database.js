const mysql = require('mysql2');
const connection = mysql.createPool({
  host: '127.0.0.1',
  port: '3307',
  user: 'bankuser',
  password: 'bankpass',
  database: 'bank_simul_r14'
});
module.exports = connection;
