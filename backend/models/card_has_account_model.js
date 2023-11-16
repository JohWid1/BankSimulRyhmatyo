const db = require('../database');


const card_has_account={
  getAll: function(callback) {
    return db.query('select * from card_has_account', callback);
  },
  getById: function(id, callback) {
    return db.query('select * from card_has_account where idcardhasaccount=?', [id], callback);
  },
  add: function(card_has_account, callback) {
      return db.query('insert into card_has_account (card_idcard, account_idaccount) values(?,?)',
      [card_has_account.card_idcard, card_has_account.account_idaccount], callback);
    },
  delete: function(id, callback) {
    return db.query('delete from card_has_account where idcardhasaccount=?', [id], callback);
  },
  update: function(id, card_has_account, callback) {    
      return db.query('update card_has_account set card_idcard=?, account_idaccount=? where idcardhasaccount=?',
      [card_has_account.card_idcard, card_has_account.account_idaccount, id], callback);
  },
}
          
module.exports = card_has_account;