namespace App
{
    partial class MainForm
    {
        /// <summary>
        /// Required designer variable.
        /// </summary>
        private System.ComponentModel.IContainer components = null;

        /// <summary>
        /// Clean up any resources being used.
        /// </summary>
        /// <param name="disposing">true if managed resources should be disposed; otherwise, false.</param>
        protected override void Dispose(bool disposing)
        {
            if (disposing && (components != null))
            {
                components.Dispose();
            }
            base.Dispose(disposing);
        }

        #region Windows Form Designer generated code

        /// <summary>
        /// Required method for Designer support - do not modify
        /// the contents of this method with the code editor.
        /// </summary>
        private void InitializeComponent()
        {
            this.grid = new System.Windows.Forms.DataGridView();
            this.tablesTreeView = new System.Windows.Forms.TreeView();
            this.conditionalPanel = new System.Windows.Forms.Panel();
            this.firstPanel = new System.Windows.Forms.Panel();
            this.nameTextBox = new System.Windows.Forms.TextBox();
            this.operatorComboBox = new System.Windows.Forms.ComboBox();
            this.valueTextBox = new System.Windows.Forms.TextBox();
            this.WHERE = new System.Windows.Forms.Label();
            this.sqlTextBox = new System.Windows.Forms.RichTextBox();
            this.label1 = new System.Windows.Forms.Label();
            this.sqlButtonRun = new System.Windows.Forms.Button();
            this.addNewButton = new System.Windows.Forms.Button();
            this.addNewPanel = new System.Windows.Forms.Panel();
            this.button1 = new System.Windows.Forms.Button();
            this.button2 = new System.Windows.Forms.Button();
            this.miasta_stats = new System.Windows.Forms.Button();
            this.wydawnictwaStats = new System.Windows.Forms.Button();
            this.label2 = new System.Windows.Forms.Label();
            this.similarBookTextBox = new System.Windows.Forms.TextBox();
            ((System.ComponentModel.ISupportInitialize)(this.grid)).BeginInit();
            this.conditionalPanel.SuspendLayout();
            this.firstPanel.SuspendLayout();
            this.SuspendLayout();
            // 
            // grid
            // 
            this.grid.BackgroundColor = System.Drawing.SystemColors.ButtonFace;
            this.grid.ColumnHeadersHeightSizeMode = System.Windows.Forms.DataGridViewColumnHeadersHeightSizeMode.AutoSize;
            this.grid.Location = new System.Drawing.Point(255, 12);
            this.grid.Name = "grid";
            this.grid.Size = new System.Drawing.Size(660, 353);
            this.grid.TabIndex = 0;
            this.grid.ColumnHeaderMouseClick += new System.Windows.Forms.DataGridViewCellMouseEventHandler(this.grid_ColumnHeaderMouseClick);
            this.grid.DataError += new System.Windows.Forms.DataGridViewDataErrorEventHandler(this.grid_DataError);
            this.grid.RowsRemoved += new System.Windows.Forms.DataGridViewRowsRemovedEventHandler(this.grid_RowsRemoved);
            this.grid.UserDeletingRow += new System.Windows.Forms.DataGridViewRowCancelEventHandler(this.grid_UserDeletingRow);
            this.grid.KeyDown += new System.Windows.Forms.KeyEventHandler(this.grid_KeyDown);
            // 
            // tablesTreeView
            // 
            this.tablesTreeView.Location = new System.Drawing.Point(31, 12);
            this.tablesTreeView.Name = "tablesTreeView";
            this.tablesTreeView.Size = new System.Drawing.Size(166, 353);
            this.tablesTreeView.TabIndex = 3;
            this.tablesTreeView.NodeMouseClick += new System.Windows.Forms.TreeNodeMouseClickEventHandler(this.TablesTreeView_NodeMouseClick);
            // 
            // conditionalPanel
            // 
            this.conditionalPanel.Controls.Add(this.firstPanel);
            this.conditionalPanel.Location = new System.Drawing.Point(472, 402);
            this.conditionalPanel.Name = "conditionalPanel";
            this.conditionalPanel.Size = new System.Drawing.Size(389, 172);
            this.conditionalPanel.TabIndex = 4;
            // 
            // firstPanel
            // 
            this.firstPanel.Controls.Add(this.nameTextBox);
            this.firstPanel.Controls.Add(this.operatorComboBox);
            this.firstPanel.Controls.Add(this.valueTextBox);
            this.firstPanel.Location = new System.Drawing.Point(3, 26);
            this.firstPanel.Name = "firstPanel";
            this.firstPanel.Size = new System.Drawing.Size(386, 21);
            this.firstPanel.TabIndex = 5;
            // 
            // nameTextBox
            // 
            this.nameTextBox.Location = new System.Drawing.Point(0, 1);
            this.nameTextBox.Name = "nameTextBox";
            this.nameTextBox.Size = new System.Drawing.Size(100, 20);
            this.nameTextBox.TabIndex = 4;
            // 
            // operatorComboBox
            // 
            this.operatorComboBox.FormattingEnabled = true;
            this.operatorComboBox.Items.AddRange(new object[] {
            "=",
            ">",
            "<",
            ">=",
            "<=",
            "=",
            "!=",
            "",
            "LIKE",
            "NOT LIKE"});
            this.operatorComboBox.Location = new System.Drawing.Point(131, 1);
            this.operatorComboBox.Name = "operatorComboBox";
            this.operatorComboBox.Size = new System.Drawing.Size(121, 21);
            this.operatorComboBox.TabIndex = 1000;
            // 
            // valueTextBox
            // 
            this.valueTextBox.Location = new System.Drawing.Point(274, 1);
            this.valueTextBox.Name = "valueTextBox";
            this.valueTextBox.Size = new System.Drawing.Size(100, 20);
            this.valueTextBox.TabIndex = 1001;
            this.valueTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.valueTextBox_KeyDown);
            // 
            // WHERE
            // 
            this.WHERE.AutoSize = true;
            this.WHERE.Location = new System.Drawing.Point(642, 386);
            this.WHERE.Name = "WHERE";
            this.WHERE.Size = new System.Drawing.Size(48, 13);
            this.WHERE.TabIndex = 1002;
            this.WHERE.Text = "WHERE";
            // 
            // sqlTextBox
            // 
            this.sqlTextBox.Location = new System.Drawing.Point(12, 402);
            this.sqlTextBox.Name = "sqlTextBox";
            this.sqlTextBox.Size = new System.Drawing.Size(380, 194);
            this.sqlTextBox.TabIndex = 1003;
            this.sqlTextBox.Text = "";
            // 
            // label1
            // 
            this.label1.AutoSize = true;
            this.label1.Location = new System.Drawing.Point(186, 386);
            this.label1.Name = "label1";
            this.label1.Size = new System.Drawing.Size(28, 13);
            this.label1.TabIndex = 1004;
            this.label1.Text = "SQL";
            // 
            // sqlButtonRun
            // 
            this.sqlButtonRun.Location = new System.Drawing.Point(160, 602);
            this.sqlButtonRun.Name = "sqlButtonRun";
            this.sqlButtonRun.Size = new System.Drawing.Size(75, 23);
            this.sqlButtonRun.TabIndex = 1005;
            this.sqlButtonRun.Text = "RUN";
            this.sqlButtonRun.UseVisualStyleBackColor = true;
            this.sqlButtonRun.Click += new System.EventHandler(this.sqlButtonRun_Click);
            // 
            // addNewButton
            // 
            this.addNewButton.Location = new System.Drawing.Point(730, 695);
            this.addNewButton.Name = "addNewButton";
            this.addNewButton.Size = new System.Drawing.Size(75, 23);
            this.addNewButton.TabIndex = 1006;
            this.addNewButton.Text = "Add new";
            this.addNewButton.UseVisualStyleBackColor = true;
            this.addNewButton.Click += new System.EventHandler(this.addNewButton_Click);
            // 
            // addNewPanel
            // 
            this.addNewPanel.Location = new System.Drawing.Point(429, 612);
            this.addNewPanel.Name = "addNewPanel";
            this.addNewPanel.Size = new System.Drawing.Size(781, 77);
            this.addNewPanel.TabIndex = 1007;
            // 
            // button1
            // 
            this.button1.Location = new System.Drawing.Point(985, 12);
            this.button1.Name = "button1";
            this.button1.Size = new System.Drawing.Size(135, 23);
            this.button1.TabIndex = 1008;
            this.button1.Text = "Ksiazki";
            this.button1.UseVisualStyleBackColor = true;
            this.button1.Click += new System.EventHandler(this.button1_Click);
            // 
            // button2
            // 
            this.button2.Location = new System.Drawing.Point(985, 61);
            this.button2.Name = "button2";
            this.button2.Size = new System.Drawing.Size(135, 23);
            this.button2.TabIndex = 1009;
            this.button2.Text = "Ksiazki - ilosc zamowien";
            this.button2.UseVisualStyleBackColor = true;
            this.button2.Click += new System.EventHandler(this.button2_Click);
            // 
            // miasta_stats
            // 
            this.miasta_stats.Location = new System.Drawing.Point(985, 111);
            this.miasta_stats.Name = "miasta_stats";
            this.miasta_stats.Size = new System.Drawing.Size(135, 23);
            this.miasta_stats.TabIndex = 1010;
            this.miasta_stats.Text = "Miasta - statystyki";
            this.miasta_stats.UseVisualStyleBackColor = true;
            this.miasta_stats.Click += new System.EventHandler(this.miasta_stats_Click);
            // 
            // wydawnictwaStats
            // 
            this.wydawnictwaStats.Location = new System.Drawing.Point(985, 157);
            this.wydawnictwaStats.Name = "wydawnictwaStats";
            this.wydawnictwaStats.Size = new System.Drawing.Size(135, 23);
            this.wydawnictwaStats.TabIndex = 1011;
            this.wydawnictwaStats.Text = "Wydawnictwa - statystyki";
            this.wydawnictwaStats.UseVisualStyleBackColor = true;
            this.wydawnictwaStats.Click += new System.EventHandler(this.wydawnictwaStats_Click);
            // 
            // label2
            // 
            this.label2.AutoSize = true;
            this.label2.Location = new System.Drawing.Point(955, 206);
            this.label2.Name = "label2";
            this.label2.Size = new System.Drawing.Size(103, 13);
            this.label2.TabIndex = 1012;
            this.label2.Text = "Podobne ksiazki do:";
            // 
            // similarBookTextBox
            // 
            this.similarBookTextBox.Location = new System.Drawing.Point(1057, 203);
            this.similarBookTextBox.Name = "similarBookTextBox";
            this.similarBookTextBox.Size = new System.Drawing.Size(164, 20);
            this.similarBookTextBox.TabIndex = 1013;
            this.similarBookTextBox.KeyDown += new System.Windows.Forms.KeyEventHandler(this.similarBookTextBox_KeyDown);
            // 
            // MainForm
            // 
            this.AutoScaleDimensions = new System.Drawing.SizeF(6F, 13F);
            this.AutoScaleMode = System.Windows.Forms.AutoScaleMode.Font;
            this.ClientSize = new System.Drawing.Size(1240, 742);
            this.Controls.Add(this.similarBookTextBox);
            this.Controls.Add(this.label2);
            this.Controls.Add(this.wydawnictwaStats);
            this.Controls.Add(this.miasta_stats);
            this.Controls.Add(this.button2);
            this.Controls.Add(this.button1);
            this.Controls.Add(this.addNewPanel);
            this.Controls.Add(this.addNewButton);
            this.Controls.Add(this.sqlButtonRun);
            this.Controls.Add(this.label1);
            this.Controls.Add(this.sqlTextBox);
            this.Controls.Add(this.conditionalPanel);
            this.Controls.Add(this.WHERE);
            this.Controls.Add(this.tablesTreeView);
            this.Controls.Add(this.grid);
            this.Name = "MainForm";
            this.Text = "Ksiegarnia Internetowa";
            ((System.ComponentModel.ISupportInitialize)(this.grid)).EndInit();
            this.conditionalPanel.ResumeLayout(false);
            this.firstPanel.ResumeLayout(false);
            this.firstPanel.PerformLayout();
            this.ResumeLayout(false);
            this.PerformLayout();

        }

        #endregion

        private System.Windows.Forms.DataGridView grid;
        private System.Windows.Forms.TreeView tablesTreeView;
        private System.Windows.Forms.Panel conditionalPanel;
        private System.Windows.Forms.TextBox valueTextBox;
        private System.Windows.Forms.ComboBox operatorComboBox;
        private System.Windows.Forms.Label WHERE;
        private System.Windows.Forms.TextBox nameTextBox;
        private System.Windows.Forms.Panel firstPanel;
        private System.Windows.Forms.RichTextBox sqlTextBox;
        private System.Windows.Forms.Label label1;
        private System.Windows.Forms.Button sqlButtonRun;
        private System.Windows.Forms.Button addNewButton;
        private System.Windows.Forms.Panel addNewPanel;
        private System.Windows.Forms.Button button1;
        private System.Windows.Forms.Button button2;
        private System.Windows.Forms.Button miasta_stats;
        private System.Windows.Forms.Button wydawnictwaStats;
        private System.Windows.Forms.Label label2;
        private System.Windows.Forms.TextBox similarBookTextBox;
    }
}

