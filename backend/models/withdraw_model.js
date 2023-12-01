const db = require('../database');

const account = {
  withdrawal: function(account, callback) {
    return db.query('call withdrawal(?, ?)', [account.sum, account.idaccount, account.idcard], callback);
  },
  //updatecredit ()
}

module.exports = account;