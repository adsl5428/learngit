Page({
  data: {
    checkboxItems: [
      { name: '有备用房', value: '0', },
      { name: '离婚', value: '1'  },
      { name: '小单边', value: '2'},
      { name: '老人房', value: '3'},
      { name: '小孩房', value: '4'}
    ],
    teshu :['0','0','0','0','0']
 //   teshu:10101
  }, 
  checkboxChange: function (e) {
    var teshu = this.data.teshu;
    console.log('checkbox发生change事件，携带value值为：', e.detail.value);

    var checkboxItems = this.data.checkboxItems, values = e.detail.value, teshu = this.data.teshu;

    for (var i = 0, lenI = checkboxItems.length; i < lenI; ++i) {
      checkboxItems[i].checked = false;
      teshu[i] =0;
      for (var j = 0, lenJ = values.length; j < lenJ; ++j) {
        if (checkboxItems[i].value == values[j]) {
          checkboxItems[i].checked = true;
          teshu[i] = 1;
          break;
        }
      }
    }

    this.setData({
      checkboxItems: checkboxItems,
      teshu: teshu
    });

    console.log('teshu：', teshu);
  },
  kindToggle: function (e) {
    var id = e.currentTarget.id, list = this.data.list;
    for (var i = 0, len = list.length; i < len; ++i) {
      if (list[i].id == id) {
        list[i].open = !list[i].open
      } else {
        list[i].open = false
      }
    }
    this.setData({
      list: list
    });
  },
  onLoad: function (options) {

  },
  onReady: function () {

  },
  onShow: function () {

  },
  onHide: function () {

  },
  onUnload: function () {

  },
  onPullDownRefresh: function () {

  },
  onReachBottom: function () {

  }
})        