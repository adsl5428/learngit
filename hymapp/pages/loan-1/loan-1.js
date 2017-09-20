Page({
  data: {

    list: [
      {
        id: 'fang',
        name: '房贷',
        open: false,
        showtitles: [
          {project:'一抵',url:'first'},
          {project: '二抵', url: 'second' }
        ]
      },
      {
        id: 'che',
        name: '车贷',
        open: false,
        showtitles: [
          { project: 'GPS', url: 'gps' },
          { project: '押车', url: 'yache' }
        ]
      },
      {
        id: 'xinyong',
        name: '信用贷',
        open: false,
        showtitles: [
          { project: '按揭房(敬请期待)', url: '' },
          { project: '打卡工资(敬请期待)', url: '' },
          { project: '其他(敬请期待)', url: '' }
        ]
      }
    ]
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