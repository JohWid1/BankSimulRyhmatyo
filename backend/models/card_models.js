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
      return db.query('insert into card (debit, credit, multicard, pin, Customer_idCustomer) values(?,?,?,?,?)',
      [card.debit, card.credit, card.multi, card.pin, card.Customer_idCustomer], callback);
    });
  },
  delete: function(id, callback) {
    return db.query('delete from card where idcard=?', [id], callback);
  },
  update: function(id, card, callback) {
    bcrypt.hash(card.pin, saltRounds, function(err, hash) {
      return db.query('update card set debit=?, credit=?, multicard=?, pin=?, Customer_idCustomer=? where idcard=?',
      [card.debit, card.credit, card.multi, card.pin, card.Customer_idCustomer, id], callback);
    });
  },
  checkpin:function(Customer_idCustomer, callback){
    return db.query('select pin from card where Customer_idCustomer=?',{Customer_idCustomer},callback);
  }

}
          
module.exports = card;