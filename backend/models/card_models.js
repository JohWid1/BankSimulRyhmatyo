const db = require('../database');
const bcrypt = require('bcryptjs');

const saltRounds=10;
const card={
  getAll: function(callback) {
    return db.query('select * from card', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from card where idcard=?', [id], callback);
  },
  add: function(card, callback) {
    bcrypt.hash(card.pin, saltRounds, function(err, hash) {
      return db.query('insert into card (idcard,debit, credit, multicard, pin, Customer_idCustomer) values(?,?,?,?,?,?)',
      [card.idcard,card.debit,card.credit,card.multicard,hash,card.Customer_idCustomer], callback);
    });
  },
  delete: function(id, callback) {
    return db.query('delete from card where idcard=?', [id], callback);
  },
  update: function(id, card, callback) {
    bcrypt.hash(card.pin, saltRounds, function(err, hash) {
      return db.query('update card set idcard=?, debit=?, credit=?,multicard=?,pin=?,Customer_idCustomer=? where idcard=?',
      [card.idcard, card.debit,card.credit,credit.multicard,card.Customer_idCustomer, hash, id], callback);
    });
  }

}
          
module.exports = card;