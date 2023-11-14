const db = require('../database');

const transaction = {
  getAll: function(callback) {
    return db.query('select * from transaction', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from transaction where id_transaction=?', [id], callback);
  },
  add: function(transaction, callback) {
    return db.query(
      'insert into transaction (action,sum,account_idaccount,cardused) values(?,?,?,?)',
      [transaction.action, transaction.sum, transaction.account, transaction.cardused],
      callback
    );
  },
  delete: function(id, callback) {
    return db.query('delete from transaction where id_transaction=?', [id], callback);
  },
  update: function(id, transaction, callback) {
    return db.query(
      'update transaction set action=?,sum=? where id_transaction=?',
      [transaction.action, transaction.sum],
      callback
    );
  }
};
module.exports = transaction;