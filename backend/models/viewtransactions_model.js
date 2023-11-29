const db = require('../database');

const viewtransactions = {
  getById: function(viewtransactions, callback) {
    return db.query('select * from transaction where cardaccountid = (select idcardhasaccount from card_has_account where (card_idcard = ? and account_idaccount = ?))',
    [viewtransactions.cardid, viewtransactions.accountid], callback);
  },
}

module.exports = viewtransactions;